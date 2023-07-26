#include <iostream>
#include "branch.h"



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
