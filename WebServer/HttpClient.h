#pragma once

#include <map>
#include "WebServer.hpp"

class HttpRequest;

class HttpClient
{
public:
    HttpClient(WebServer::ClientSocket *sock);
    virtual ~HttpClient();

    bool addParam(const std::string & param);
    void debug() const;

    HttpClient *setServer(WebServer *srv);
    const WebServer *getServer() const;
    HttpRequest * getRequest() const;

    HttpClient * addHeader(const std::string &key, const std::string & value);
    std::string getRespondStringCode(unsigned short code);
    void sendResponse();
    int respondCode(int respondCode = -1);
    bool readNextParam();

    std::string debugResponse;
	const WebServer::ClientSocket * getConstSocket() const;

private:
    WebServer::ClientSocket * getSocket() const;
    unsigned int getRespondSize();

private:
    WebServer::ClientSocket * const socket;
    WebServer *server;
    std::map<std::string, std::string> header;
    HttpRequest *req;
    int responseCode;
};
