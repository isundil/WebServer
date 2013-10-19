#include <sstream>
#include "SessionManager.h"
#include "WebServer.hpp"
#include "HttpClient.h"
#include "HttpRequest.h"
#include "HashGenerator.h"
#include "Session.h"
#include "Response.h"
#include "HtmlRootElement.h"
#include "Meta.h"

HttpClient::HttpClient(WebServer::ClientSocket *s) : socket(s)
{
    req = new HttpRequest();
    addHeader("Cache - Control", "no-cache")->addHeader("Pragma", "no-cache");
    addHeader("X-Cnection", "close");
    responseCode = 200;
    session = NULL;
    response = new Response();
}

HttpClient::~HttpClient()
{
    delete socket;
    delete req;
    delete response;
}

std::string HttpClient::getRespondStringCode(unsigned short code)
{
    std::map<int, std::string> codes;
    codes[100] = "Continue";
    codes[101] = "Switching Protocols";
    codes[200] = "OK";
    codes[201] = "Created";
    codes[202] = "Accepted";
    codes[203] = "Non-Authoritative Information";
    codes[204] = "No Content";
    codes[205] = "Reset Content";
    codes[206] = "Partial Content";
    codes[300] = "Multiple Choices";
    codes[301] = "Moved Permanently";
    codes[302] = "Found";
    codes[303] = "See Other";
    codes[304] = "Not Modified";
    codes[305] = "Use Proxy";
    codes[307] = "Temporary Redirect";
    codes[400] = "Bad Request";
    codes[401] = "Unauthorized";
    codes[402] = "Payment Required";
    codes[403] = "Forbidden";
    codes[404] = "Not Found";
    codes[405] = "Method Not Allowed";
    codes[406] = "Not Acceptable";
    codes[407] = "Proxy Authentication Required";
    codes[408] = "Request Time-out";
    codes[409] = "Conflict";
    codes[410] = "Gone";
    codes[411] = "Length Required";
    codes[412] = "Precondition Failed";
    codes[413] = "Request Entity Too Large";
    codes[414] = "Request-URI Too Large";
    codes[415] = "Unsupported Media Type";
    codes[416] = "Requested range not satisfiable";
    codes[417] = "Expectation Failed";
    codes[500] = "Internal Server Error";
    codes[501] = "Not Implemented";
    codes[502] = "Bad Gateway";
    codes[503] = "Service Unavailable";
    codes[504] = "Gateway Time-out";
    codes[505] = "HTTP Version not supported";
    return codes [code];
}

unsigned int HttpClient::getRespondSize()
{
    return response->length();
}

int HttpClient::respondCode(int code)
{
    if (code != -1)
        responseCode = code;
    return responseCode;
}

bool HttpClient::readNextParam()
{
    std::string line = this->getSocket()->readLine();
    return this->addParam(line);
}

bool HttpClient::addParam(const std::string &param)
{
    if (param == "")
        return false;
    size_t pos;
    if ((pos = param.find(":")) == param.npos)
        req->setRequest(param);
    else
        req->addParam(param.substr(0, pos), param.substr(pos + 1));
    return (true);
}

HttpClient & HttpClient::readData()
{
    const unsigned int dataLen = req->getDataLength();
    char * buffer;

    if (req->getData().size() != 0 || dataLen == 0)
        return *this;
    buffer = new char[dataLen +1];
    this->getSocket()->readBytes(buffer, dataLen);
    req->parseData(buffer);
    delete [] buffer;
    return *this;
}

void HttpClient::sessionUpdate()
{
    if (session)
    {
        getRequest()->getCookies()->updateExpire("sessid", time(NULL) + session->getDefaultExpire());
        session->updateTime();
    }
}

void HttpClient::sendResponseHeader()
{
    sessionUpdate();
    addHeader("Content-Type", responseGetConst()->getContentType());
    if (dynamic_cast<html::HtmlRootElement *> (response->getElement()) != NULL)
    {
        html::Meta & meta = ((html::HtmlRootElement *)response->getElement())->getMeta();
        meta.setIdentifier("http://" + getRequest()->getHost() + getRequest()->getRequestUrl()); //TODO https ?
    }
    std::stringstream ss;
    ss << getRequest()->getHttpVersion() << " " << responseCode << " " << getRespondStringCode(responseCode) << std::endl;
    for (auto i = header.cbegin(); i != header.cend(); i++)
    {
        ss << (*i).first << ": " << (*i).second << std::endl;
    }
    if (getRequest()->getCookies()->hasNew())
        ss << getRequest()->getCookies()->getString();
    ss << "Content-Length" << ": " << getRespondSize() << std::endl << std::endl;
    getSocket()->write(ss.str());
}

void HttpClient::sendResponseBody()
{
    getSocket()->write(response->getValue());
}

void HttpClient::sendResponse()
{
    this->sendResponseHeader();
    this->sendResponseBody();
}

CookieManager * HttpClient::getCookies()
{
    return this->getRequest()->getCookies();
}

HttpClient * HttpClient::setServer(WebServer *srv)
{
    server = srv;
    return this;
}

const WebServer *HttpClient::getServer() const
{
    return server;
}

WebServer::ClientSocket * HttpClient::getSocket() const
{
    return socket;
}

const WebServer::ClientSocket * HttpClient::getConstSocket() const
{
    return socket;
}

void HttpClient::debug() const
{
    this->req->debug();
}

HttpRequest * HttpClient::getRequest() const
{
    return this->req;
}

HttpClient * HttpClient::addHeader(const std::string &key, const std::string & value)
{
    header[key] = value;
    return this;
}

Session * HttpClient::sessionGetOrNull()
{
    if (session == NULL)
    {
        SessionManager::refresh();
        session = SessionManager::getSession(getRequest()->getCookies()->getValue("sessid", std::string("")));
    }
	return session;
}

Session * HttpClient::sessionGetOrCreate()
{
	Session * sess = sessionGetOrNull();
	if (sess)
		return sess;
	const std::string hash = HashGenerator::generateHash(*this);
	getRequest()->getCookies()->setValue("sessid", hash);
	session = SessionManager::createNewSession(hash);
	return session;
}

void HttpClient::sessionDestroy()
{
    SessionManager::destroy(getRequest()->getCookies()->getValue<std::string>("sessid", ""));
    getRequest()->getCookies()->destroy("sessid");
    session = NULL;
}

Response * HttpClient::responseGet()
{
    return response;
}

const Response * HttpClient::responseGetConst() const
{
    return response;
}

const std::map<std::string, std::string> HttpClient::getPostData() const
{
    return req->getData();
}
