#include "WebServer.hpp"
#include "HttpClient.h"
#include "Response.h"
#include "RawRootElement.h"
#include "Util.h"

WebServer::MappedDirectory::MappedDirectory(const std::string &drive, const std::string & url, bool recu) :
    realPath(drive), virtualPath(url), recursive(recu)
{
    virtualPathPart = string_split(virtualPath, '/');
}

WebServer::MappedDirectory::~MappedDirectory()
{}

std::string WebServer::MappedDirectory::match(const std::string &url)
{
    std::list<std::string> urlParts = string_split(url, '/');
    if (virtualPathPart.size() > urlParts.size())
        return "";

    auto i = virtualPathPart.cbegin();
    auto j = urlParts.cbegin();
    for (; i != virtualPathPart.cend() && j != urlParts.cend(); i++, j++)
        if (*i != *j)
            return "";
    return realPath;
}
