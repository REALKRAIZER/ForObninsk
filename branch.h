#ifndef BRANCHESCOMPRASSION_H
#define BRANCHESCOMPRASSION_H
#include <map>
#include <set>
#include <string>
#include <list>

#ifdef  __cplusplus
extern "C" {
#endif

namespace Obninsk
{

struct PackageInfo
{
    std::string version;
};

class BranchComparing;
/*добавь оболочку над итераторами list, чтобы стандартные шаблоны обращали к итератору класса так:
Branch::iterator*/
class Branch
{
    friend class BranchComparing;//потом попробуй сделать дружественным метод
private:
    std::multimap<std::string, PackageInfo> packages_;
public:
    Branch(const std::string &namebranch);

    Branch(const Branch &) = default;
    Branch(Branch &&) = default;
    Branch &operator=(const Branch &) = default;
    Branch &operator=(Branch &&) = default;

    std::multimap<std::string, PackageInfo>::iterator begin() {return packages_.begin();}
    std::multimap<std::string, PackageInfo>::iterator end() {return packages_.end();}

    virtual ~Branch() {};
};
//сделай пседонимы огромным названиям типов
//сократи названия методов
class BranchComparing
{
private:
    mutable Branch firstBranch_;
    mutable Branch secondBranch_;

    int compareVersions(const std::string, const std::string);
public:
    BranchComparing(const char *firstStr, const char *secondStr) :
        firstBranch_(firstStr), secondBranch_(secondStr) {}
    BranchComparing(const Branch &firstBranch, const Branch &secondBranch) :
        firstBranch_(firstBranch), secondBranch_(secondBranch) {}

    //void setBranches(const std::string, const std::string);
    BranchComparing(const BranchComparing &) = default;
    BranchComparing(BranchComparing &&) = default;
    BranchComparing &operator=(const BranchComparing &) = default;
    BranchComparing &operator=(BranchComparing &&) = default;

    std::list<std::pair<std::string, PackageInfo>>  getPackagesOnlyInFirst();//озвращай только имя пакета, а не всю инфу
    std::list<std::pair<std::string, PackageInfo>>  getPackagesOnlyInSecond();
    std::set<std::string>                           getNamePackagesVersionMoreThanSecond();

    virtual ~BranchComparing() {};
};

}

#ifdef  __cplusplus
}
#endif

#endif // BRANCHESCOMPRASSION_H

