#pragma once
#include <list>
#include "HtmlRootElement.h"
#include "AWebPage.h"

class DirContentRootElem : public html::HtmlRootElement
{
public:
    DirContentRootElem(const std::string & path, const std::string & virtualPath);
    virtual ~DirContentRootElem();

public: //public nested
    typedef struct
    {
        std::string name;
        std::string sizeStr;
        long long size;
        bool isDir;
    } t_file;
private:
    std::list<t_file> *readDir(const std::string &dir);
};
