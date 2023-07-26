#include <iostream>
#include <fstream>
#include <unistd.h>
#include "branch.h"
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

                default: /* '?' */
                    std::cerr << "Some problems:(" << std::endl;
                    exit(EXIT_FAILURE);

            }
        }
        Obninsk::BranchCompression compression(firstBranch, secondBranch);

        using json = nlohmann::json;
        json data;
        data["only_in_first"] = json::array();
        data["only_in_second"] = json::array();
        //data["VersionMoreThanSecond"] = json::array();

        auto temp = compression.getPackagesOnlyInFirst();
        for(auto it = temp.begin(); it != temp.end(); ++it) {
            data["only_in_first"].push_back(it->first);
        }
        temp = compression.getPackagesOnlyInSecond();
        for(auto it = temp.begin(); it != temp.end(); ++it) {
            data["only_in_second"].push_back(it->first);
        }
        /*temp = compression.getNamePackagesVersionMoreThanSecond();
        for(auto it = temp.begin(); it != temp.end(); ++it) {
            data["only_in_second"].push_back(*it);
        }*/
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
        std::cout << ex.what() << std::endl;
    }
    catch(...) {return 1;}

    return 0;
}
