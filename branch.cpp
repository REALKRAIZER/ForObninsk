#include "branch.h"
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <string>
#include <exception>
#include <regex>
#include <algorithm>
#include <iostream>
namespace Obninsk
{
size_t writeCallback(char *ptr, size_t size, size_t nmemb, std::string *userdata)
{
    size_t realsize = size * nmemb;
    userdata->append(ptr, realsize);

    return realsize;
}

Branch::Branch(const std::string &namebranch)
{
    CURL *curl;
    std::string response;

    //получаем json с сервера
    curl = curl_easy_init();
    if(curl) {
        std::string url = "https://rdb.altlinux.org/api/export/branch_binary_packages/" + namebranch;//хардкод
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());//хардкод

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        CURLcode code = curl_easy_perform(curl);
        try {
            if(code != CURLE_OK)
                throw std::runtime_error(std::string("Ошибка выполнения GET-запроса: ") + curl_easy_strerror(code));
        }
        catch(std::exception &ex) {
            curl_easy_cleanup(curl);
            throw;
        }

        curl_easy_cleanup(curl);
    }

    //парсим json
    using json = nlohmann::json;

    json js = json::parse(response);
    for(const auto &it : js["packages"])
        packages_.insert( std::make_pair(it["name"], PackageInfo {it["version"]}) );
}
bool comp(const std::pair<std::string, PackageInfo> &p1, const std::pair<std::string, PackageInfo> &p2)
{
    return p1.first < p2.first;
}
std::list<std::pair<std::string, PackageInfo>> BranchComparing::getPackagesOnlyInFirst()//set
{
    std::list<std::pair<std::string, PackageInfo>> result;
    set_difference(firstBranch_.begin(), firstBranch_.end(), secondBranch_.begin(), secondBranch_.end(), std::back_inserter(result), comp);
    return result;
}
std::list<std::pair<std::string, PackageInfo>> BranchComparing::getPackagesOnlyInSecond()
{
    std::list<std::pair<std::string, PackageInfo>> result;
    set_difference(secondBranch_.begin(), secondBranch_.end(), firstBranch_.begin(), firstBranch_.end(), std::back_inserter(result), comp);
    return result;
}
int BranchComparing::compareVersions(const std::string first, const std::string second)
{//return 1 -> first > second, -1 -> first < second, 0 -> first == second

    std::regex pattern("\\.");

    std::sregex_token_iterator end;
    std::sregex_token_iterator it1(first.begin(), first.end(), pattern, -1);
    std::sregex_token_iterator it2(second.begin(), second.end(), pattern, -1);

    while(it1 != end && it2 != end) {
        int component1 = std::stoi(*it1);
        int component2 = std::stoi(*it2);

        if(component1 > component2)
            return 1;
        else if(component1 < component2)
            return -1;
        ++it1;
        ++it2;
    }

    if(it1 != end && std::stoi(*it1) != 0)
        return 1;
    else if(it2 != end && std::stoi(*it2) != 0)
        return -1;

    return 0;
}
std::set<std::string> BranchComparing::getNamePackagesVersionMoreThanSecond()
{
    std::set<std::string> packages;

    for(auto it = firstBranch_.begin(); it != firstBranch_.end(); ++it) {
        const std::string &packageName = it->first;
        const std::string &versionFirst = it->second.version;

        auto range = secondBranch_.packages_.equal_range(packageName);

        for(auto secondIt = range.first; secondIt != range.second; ++secondIt) {
            const std::string &versionSecond = secondIt->second.version;

            try {
                if(compareVersions(versionFirst, versionSecond) > 0) {
                    packages.insert(packageName);
                    break;
                }
            }
            catch(const std::invalid_argument &ex) {
                std::cerr << "Неправильный аргумент: " << ex.what() << std::endl;
                packages.insert("Ошибка при сравнении");
                continue;
            }
        }
    }
    return packages;
}

}



















