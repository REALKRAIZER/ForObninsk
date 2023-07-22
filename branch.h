#ifndef BRANCHESCOMPRASSION_H
#define BRANCHESCOMPRASSION_H
#include <list>
#include <string>

#ifdef  __cplusplus
extern "C" {
#endif

namespace Obninsk
{

struct Package
{
    std::string name;
    std::string version;
};

class Branch//добавь итераторы
{
private:
    std::list<Package> packages_;
public:
    Branch(const std::string &namebranch);

    Branch(const Branch &) = default;
    Branch(Branch &&) = default;
    Branch &operator=(const Branch &) = default;
    Branch &operator=(Branch &&) = default;

    std::list<Package>::iterator begin() {return packages_.begin();}
    std::list<Package>::iterator end() {return packages_.end();}
    virtual ~Branch() {};
};

}

#ifdef  __cplusplus
}
#endif

#endif // BRANCHESCOMPRASSION_H

