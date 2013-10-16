#ifdef _WIN32
# include <Windows.h>
# include <fileapi.h>
#endif //WIN
#include "DirContentRootElem.h"
#include "HttpError.h"

DirContentRootElem::DirContentRootElem(const std::string & path, const std::string & virtualPath) :
            html::HtmlRootElement("Index of " + path)
{
    auto dirContent = this->readDir(path);
    for (auto i = dirContent->cbegin(); i != dirContent->cend(); i++)
        if ((*i).isDir)
            (*this) << "D | " + (*i).name;
        else
            (*this) << "F | " + (*i).name + " (" + (*i).sizeStr + " o)";
    delete dirContent;
}

DirContentRootElem::~DirContentRootElem()
{}

#ifdef _WIN32
static inline std::string wcharToString(const wchar_t *in)
{
    char * buffer;
    std::string result;
    const int len = wcslen(in);

    buffer = new char[len + 1];
    for (int i = 0; i <= len; i++)
        buffer[i] = (char)in[i];
    result = std::string(buffer);
    delete [] buffer;
    return result;
}

static inline void parseFile(const WIN32_FIND_DATA &fileData, std::list<DirContentRootElem::t_file> *list)
{
    DirContentRootElem::t_file dirElem;
    std::stringstream ss;

    dirElem.isDir = (fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
    dirElem.name = wcharToString(fileData.cFileName);
    dirElem.size = fileData.nFileSizeLow;
    ss << dirElem.size;
    dirElem.sizeStr = ss.str();
    list->push_back(dirElem);
}
#endif

std::list<DirContentRootElem::t_file> *DirContentRootElem::readDir(const std::string & path)
{
    auto result = new std::list<DirContentRootElem::t_file>();
#ifdef _WIN32
    WIN32_FIND_DATA fileData;
    HANDLE dir;
    wchar_t *buf = new wchar_t[path.length() + 2];

    for (size_t i = 0; i < path.length(); i++)
        buf[i] = path.at(i);
    buf[path.length()] = '*';
    buf[path.length() +1] = '\0';

    dir = FindFirstFile(buf, &fileData);
    delete [] buf;

    if (dir == INVALID_HANDLE_VALUE)
        throw Error404();

    parseFile(fileData, result);
    while (FindNextFile(dir, &fileData))
    {
        parseFile(fileData, result);
    } 
#endif //TODO linux
    return result;
}