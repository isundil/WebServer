#include "WebServer.hpp"
#include "HttpClient.h"
#include "Response.h"
#include "RawRootElement.h"

WebServer::MappedDirectory::MappedDirectory(const std::string &drive, const std::string & url, bool recu) :
    realPath(drive), virtualPath(url), recursive(recu)
{
}

WebServer::MappedDirectory::~MappedDirectory()
{}

std::string WebServer::MappedDirectory::match(const std::string &url)
{
    return "";
}
