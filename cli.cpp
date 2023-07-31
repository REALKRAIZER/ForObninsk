#include <iostream>
#include <fstream>
#include <unistd.h>
#include <branch.h>
#include <nlohmann/json.hpp>


int main(int argc, char *argv[])
{
    int opt;
    const char *firstBranch, *secondBranch, *filename = NULL;
    try {
        while((opt = getopt(argc, argv, "1:2:f::")) != -1) {
            switch(opt)
            {
                case '1':
                    firstBranch = optarg;
                    break;
                case '2':
                    secondBranch = optarg;
                    break;
                case 'f':
                    filename = optarg;
                    break;

                default:
                    std::cerr << "Some problems:(" << std::endl;
                    exit(EXIT_FAILURE);

            }
        }
        Obninsk::BranchComparing comparing(firstBranch, secondBranch);

        using json = nlohmann::json;
        json data;
        data["only_in_first"] = json::array();
        data["only_in_second"] = json::array();
        data["version_more_than_second"] = json::array();

        auto temp = comparing.getPackagesOnlyInFirst();
        for(auto it = temp.begin(); it != temp.end(); ++it) {
            data["only_in_first"].push_back(it->first);
        }
        temp = comparing.getPackagesOnlyInSecond();
        for(auto it = temp.begin(); it != temp.end(); ++it) {
            data["only_in_second"].push_back(it->first);
        }
        auto temp2 = comparing.getNamePackagesVersionMoreThanSecond();
        for(auto it = temp2.begin(); it != temp2.end(); ++it) {
            data["version_more_than_second"].push_back(*it);
        }
        if(filename != NULL) {
            std::ofstream fout(filename);
            if(fout.is_open()) {
                fout << data.dump(4);
                std::cout << "Json в файле!!!" << std::endl;
                fout.close();
            }
            else
                std::cout << "Не удалось открыть файл" << std::endl;
        }
        else
            std::cout << data.dump(4);

    }
    catch(const std::exception &ex) {
        std::cerr << "Ошибка: " << ex.what() << std::endl;
    }
    catch(...) {
        std::cerr << "Неизвестная ошибка" << std::endl;
    }

    return 0;
}
