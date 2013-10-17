#ifdef _WIN32
# include <Windows.h>
# include <fileapi.h>
#else
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <dirent.h>
#endif //WIN
#include "DirContentRootElem.h"
#include "Link.h"
#include "HttpError.h"

DirContentRootElem::DirContentRootElem(const std::string & path, const std::string & virtualPath) :
            html::HtmlRootElement("Index of " + virtualPath)
{
    std::string _path = path;
    std::string parentUrl;
    std::list<DirContentRootElem::t_file> *dirContent;

    if (path.at(path.length() - 1) != '/')
        _path += "/";
    if (virtualPath.at(virtualPath.length() - 1) != '/')
        parentUrl = virtualPath.substr(0, virtualPath.find_last_of('/'));
    else
    {
        parentUrl = virtualPath.substr(0, virtualPath.find_last_of('/'));
        parentUrl = virtualPath.substr(0, parentUrl.find_last_of('/'));
    }
    if (parentUrl.length() == 0)
        parentUrl = "/";
    dirContent = this->readDir(_path);
    (*this) << new html::Link(parentUrl, std::string("D | Parent directory"));
    for (auto i = dirContent->cbegin(); i != dirContent->cend(); i++)
    {
        if ((*i).name == ".." || (*i).name == ".")
            continue;
        else if ((*i).isDir)
            (*this) << new html::Link(virtualPath + "/" + (*i).name, "D | " + (*i).name);
        else
            (*this) << new html::Link(virtualPath + "/" + (*i).name, "F | " + (*i).name + " (" + (*i).sizeStr + " o)");
    }
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
    buf[path.length() + 0] = '*';
    buf[path.length() + 1] = '\0';

    dir = FindFirstFile(buf, &fileData);
    delete [] buf;

    if (dir == INVALID_HANDLE_VALUE)
        throw Error404();

    parseFile(fileData, result);
    while (FindNextFile(dir, &fileData))
    {
        parseFile(fileData, result);
    } 
#else
	struct dirent *fileData;
	struct stat fileStat;
	DIR *dir = opendir(path.c_str());
	DirContentRootElem::t_file file;

	if (!dir)
		throw Error404();
	while ((fileData = readdir(dir)) != NULL)
	{
		std::stringstream ss;
		file.name= fileData->d_name;
		stat((path +"/" +file.name).c_str(), &fileStat);
		file.isDir = S_ISDIR(fileStat.st_mode);
		file.size = fileStat.st_size;
		ss << file.size;
		file.sizeStr = ss.str();
		result->push_back(file);
	}
	closedir(dir);
#endif
    return result;
}
