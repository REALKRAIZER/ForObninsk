#include "branch.h"
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <string>
#include <exception>
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
    for(const auto &it : js["packages"]) {
        Package pack {it["name"], it["version"]};
        packages_.push_back(std::move(pack));
    }
}

}



















