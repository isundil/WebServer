#include <fstream>
#include "HttpError.h"
#include "HttpClient.h"
#include "WebServer.hpp"

WebServer::FileElement::FileElement(const std::string & p) : path(p)
{
    stream = new std::ifstream(path, std::ifstream::in | std::ifstream::binary);
    if (!stream->is_open())
        throw Error404();
    size = stream->tellg();
    stream->seekg(0, std::ios::end);
    size = (long long)stream->tellg() - size;
    stream->seekg(0);
}

WebServer::FileElement::~FileElement()
{
    stream->close();
    delete stream;
}

const std::string WebServer::FileElement::getValue()
{
    return "";
}

unsigned int WebServer::FileElement::length()
{
    return (unsigned int)this->size;
}

void WebServer::FileElement::send(ClientSocket * sock)
{
    char * buf = new char[1024 + 1];
    unsigned int rd, realRd;

    for (long long i = 0; i < size;)
    {
        rd = (unsigned int) ((size - i < 1024) ? size - i : 1024);
        stream->read(buf, rd);
        realRd = (int)stream->gcount();
        if (realRd != rd)
            throw std::runtime_error("Cannot read from file");
        sock->write(buf, realRd);
        i += realRd;
    }
}

std::string WebServer::FileElement::getExtension() const
{
    std::string result = path;

    result.erase(0, result.find_last_of("./") +1);
    return result;
}

std::string WebServer::FileElement::getMimeType(const std::map<std::string, std::string> &mime) const
{
    const std::string ext = getExtension();
    const auto it = mime.find(ext);

    if (it != mime.cend())
        return (*it).second;
    //TODO default mime
    return "";
}