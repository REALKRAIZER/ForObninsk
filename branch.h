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

class BranchCompression;
class Branch//добавь оболочку над итераторами
{
    friend class BranchCompression;//потом попробуй сделать дружественным метод
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
class BranchCompression
{
private:
    mutable Branch first_;
    mutable Branch second_;

    int compareVersions(const std::string, const std::string);
public:
    BranchCompression(const char *firstStr, const char *secondStr) :
        first_(firstStr), second_(secondStr) {}
    BranchCompression(const Branch &firstBranch, const Branch &secondBranch) :
        first_(firstBranch), second_(secondBranch) {}

    //void setBranches(const std::string, const std::string);
    BranchCompression(const BranchCompression &) = default;
    BranchCompression(BranchCompression &&) = default;
    BranchCompression &operator=(const BranchCompression &) = default;
    BranchCompression &operator=(BranchCompression &&) = default;

    std::list<std::pair<std::string, PackageInfo>>  getPackagesOnlyInFirst();//озвращай только имя пакета, а не всю инфу
    std::list<std::pair<std::string, PackageInfo>>  getPackagesOnlyInSecond();
    std::set<std::string>                           getNamePackagesVersionMoreThanSecond();

    virtual ~BranchCompression() {};
};

}

#ifdef  __cplusplus
}
#endif

#endif // BRANCHESCOMPRASSION_H

