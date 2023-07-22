#include <iostream>
#include "branch.h"


using namespace std;

int main()
{
    try {
        Obninsk::Branch branch("p10");
    }
    catch(const std::exception &ex) {
        std::cout << ex.what() << std::endl;
    }
    catch(...) {return 1;}
    return 0;
}
