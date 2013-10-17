#ifdef _WIN32
# include <Windows.h>
# include <fileapi.h>
#else
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
#endif
#include "WebServer.hpp"
#include "HttpClient.h"
#include "Response.h"
#include "RawRootElement.h"
#include "HttpError.h"
#include "Util.h"

WebServer::MappedDirectory::MappedDirectory(const std::string &drive, const std::string & url, bool recu, bool show) :
    realPath(drive), virtualPath(url), recursive(recu), showContent(show)
{
    virtualPathPart = string_split(virtualPath, '/');
}

WebServer::MappedDirectory::~MappedDirectory()
{}

std::string WebServer::MappedDirectory::getExtendedPath(const std::list<std::string> & urlParts, std::list<std::string>::const_iterator &pos)
{
    std::string result = realPath;

    if (recursive == false)
        return "";
    for (; pos != urlParts.cend(); pos++)
        result += "/" + *pos;
    return result;
}

std::string WebServer::MappedDirectory::doMatch(const std::string &url)
{
    std::list<std::string> urlParts = string_split(url, '/');

    auto i = virtualPathPart.cbegin();
    auto j = urlParts.cbegin();
    for (; i != virtualPathPart.cend() && j != urlParts.cend(); i++, j++)
    {
        for (; i != virtualPathPart.cend() && *i == ""; i++);
        for (; j != urlParts.cend() && *j == ""; j++);
        if (j == urlParts.cend() && i != virtualPathPart.cend())
            return "";
        else if (j == urlParts.cend())
            return realPath;
        else if (i == virtualPathPart.cend())
            return getExtendedPath(urlParts, j);
        if (*i != *j)
            return "";
    }
    return realPath;
}

bool WebServer::MappedDirectory::isDirectory(const std::string &filename)
{
#ifdef _WIN32
    wchar_t *buf = new wchar_t [filename.length() +1];
    for (size_t i = 0; i < filename.length(); i++)
        buf[i] = filename.at(i);
    buf[filename.length()] = '\0';
    auto result = GetFileAttributes(buf);
    delete [] buf;
    return (result & FILE_ATTRIBUTE_DIRECTORY) != 0;
#else
	struct stat m_stat;
	stat(filename.c_str(), &m_stat);
	return S_ISDIR(m_stat.st_mode);
#endif
    return false;
}

std::string WebServer::MappedDirectory::match(const std::string &url, bool &isD)
{
    std::string result = doMatch(url);
    if (result == "")
        return "";
    isD = isDirectory(result);
    if (isD && !showContent)
        throw Error403();
    return result;
}
