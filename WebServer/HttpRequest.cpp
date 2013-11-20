#include <iostream>
#include <map>
#include "HttpRequest.h"
#include "FileField.h"
#include "Util.h"

enum HttpRequest::reqtype HttpRequest::stringToReqType(const std::string &input)
{
    std::map<std::string, const HttpRequest::reqtype> map;
    map.insert(std::pair<std::string, const HttpRequest::reqtype>("OPTIONS", HttpRequest::reqtype::option));
    map.insert(std::pair<std::string, const HttpRequest::reqtype>("GET", HttpRequest::reqtype::get));
    map.insert(std::pair<std::string, const HttpRequest::reqtype>("HEAD", HttpRequest::reqtype::head));
    map.insert(std::pair<std::string, const HttpRequest::reqtype>("POST", HttpRequest::reqtype::post));
    map.insert(std::pair<std::string, const HttpRequest::reqtype>("PUT", HttpRequest::reqtype::put));
    map.insert(std::pair<std::string, const HttpRequest::reqtype>("DELETE", HttpRequest::reqtype::del));
    map.insert(std::pair<std::string, const HttpRequest::reqtype>("TRACE", HttpRequest::reqtype::trace));
    map.insert(std::pair<std::string, const HttpRequest::reqtype>("CONNECT", HttpRequest::reqtype::connect));
    return map[input];
}

const std::string HttpRequest::reqTypeToString(enum HttpRequest::reqtype input)
{
    std::map<const HttpRequest::reqtype, std::string> map;
    map.insert(std::pair<const HttpRequest::reqtype, std::string>(HttpRequest::reqtype::option, "OPTIONS"));
    map.insert(std::pair<const HttpRequest::reqtype, std::string>(HttpRequest::reqtype::get, "GET"));
    map.insert(std::pair<const HttpRequest::reqtype, std::string>(HttpRequest::reqtype::head, "HEAD"));
    map.insert(std::pair<const HttpRequest::reqtype, std::string>(HttpRequest::reqtype::post, "POST"));
    map.insert(std::pair<const HttpRequest::reqtype, std::string>(HttpRequest::reqtype::put, "PUT"));
    map.insert(std::pair<const HttpRequest::reqtype, std::string>(HttpRequest::reqtype::del, "DELETE"));
    map.insert(std::pair<const HttpRequest::reqtype, std::string>(HttpRequest::reqtype::trace, "TRACE"));
    map.insert(std::pair<const HttpRequest::reqtype, std::string>(HttpRequest::reqtype::connect, "CONNECT"));
    return map[input];
}

HttpRequest::HttpRequest()
{
    request = std::pair<enum reqtype, std::string>(reqtype::invalid, "");
    httpVersion = "HTTP/1.1";
}

HttpRequest::~HttpRequest()
{}

HttpRequest *HttpRequest::addParam(const std::string & key, const std::string & value)
{
	if (key == "Cookie")
		evalCookies(value);
    paramList.insert(paramList.end(), std::pair<std::string, const std::string>(epur_begin_str(key.c_str()), epur_begin_str(value.c_str())));
    return this;
}

HttpRequest *HttpRequest::setRequest(const std::string & request)
{
    int pos = request.find(' ');
    std::string first = request.substr(0, pos);
    this->request = std::pair<enum reqtype, std::string>(HttpRequest::stringToReqType(first), request.substr(pos +1));
    std::list<std::string> requestFields = string_split(this->request.second, ' ');
    for (auto i = requestFields.cbegin(); i != requestFields.cend(); i++)
    {
        if (i == requestFields.cbegin())
        {
            std::string::size_type pos;
            std::string params;

            requestUrl = url_decode(*(i));
            if ((pos = requestUrl.find("?")) != requestUrl.npos)
            {
                params = requestUrl.substr(pos +1);
                requestUrl.erase(pos);
                this->parseData(params.c_str());
            }
        }
        else
            httpVersion = *(i);
    }
    return this;
}

bool HttpRequest::isValid() const
{
    return request.first != HttpRequest::reqtype::invalid;
}

void HttpRequest::debug() const
{
    std::cout << "REQUEST: " << request.first << std::endl;
    for (auto i = paramList.cbegin(); i != paramList.cend(); i++)
        std::cout << (*i).first << " => " << (*i).second << std::endl;
}

const std::map<std::string, std::string> HttpRequest::getData() const
{
    return data;
}

const std::map<std::string, FileInputData *> HttpRequest::getFileData() const
{
    return fileData;
}

unsigned int HttpRequest::getDataLength() const
{
    for (auto i = paramList.cbegin(); i != paramList.cend(); i++)
    {
        if ((*i).first == "Content-Length")
        {
            unsigned int result;
            std::stringstream ss((*i).second);
            ss >> result;
            return result;
        }
    }
    return 0;
}

void HttpRequest::parseData(const char *buffer)
{
    std::list<std::string> data = string_split(buffer, '&');
    size_t pos;

    for (auto i = data.cbegin(); i != data.cend(); i++)
    {
        pos = (*i).find("=");
        if (pos == (*i).npos)
            continue;
        this->data[(*i).substr(0, pos)] = url_decode((*i).substr(pos +1));
    }
}

void HttpRequest::parseMultipart(const std::pair<std::stringstream *, unsigned int> &line)
{
    unsigned long remainingLen = line.second;
    std::string buffer;
    std::string firstLineStr;
    std::map<std::string, std::string> parameters;
    std::list<std::string> paramsList;
    std::streampos begin;

    std::getline(*(line.first), firstLineStr);
    remainingLen -= firstLineStr.length() + 1;
    paramsList = string_split(firstLineStr, ';');
    for each (auto i in paramsList)
    {
        size_t pos = i.find_first_of(":=");
        if (pos == i.npos)
            continue;
        parameters[trimMultipartParameter(i.substr(0, pos))] = trimMultipartParameter(i.substr(pos + 1));
    }
    if (parameters.find("Content-Disposition") == parameters.end())
        return;
    if (parameters.find("filename") == parameters.end())
    {
        std::string result;

        std::getline(*(line.first), result);
        std::getline(*(line.first), result);
        if (result[0] != '\0' && result[result.length() - 1] == '\r')
            result = result.substr(0, result.length() -1);
        this->data[parameters["name"]] = url_decode(result);
    }
    else
    {
        std::getline(*(line.first), firstLineStr);
        remainingLen -= firstLineStr.length() + 1;
        std::getline(*(line.first), firstLineStr);
        remainingLen -= firstLineStr.length() + 1;
        fileData[parameters["name"]] = new FileInputData(parameters["filename"], line.first, line.second - remainingLen, line.second -2);
    }
    line.first->seekg(line.second - remainingLen, std::ios_base::beg);
}

std::string HttpRequest::trimMultipartParameter(const std::string &in)
{
    std::string result;
    char *buffer;
    int begin = 0;
    int end = in.length();

    buffer = new char[in.length() + 1];
    memcpy(buffer, in.c_str(), in.length() + 1);

    while (buffer[begin] == ' ')
        begin++;
    if (buffer[begin] != '"')
        while (buffer[end] == ' ')
            buffer[end--] = '\0';
    else
    {
        begin++;
        end = begin + 1;
        while (buffer[end] != '"' && buffer[end])
            end++;
        buffer[end] = '\0';
    }
    result = std::string(&buffer[begin]);
    delete [] buffer;
    return result;
}

const std::string HttpRequest::getHost() const
{
    for (auto i = paramList.cbegin(); i != paramList.cend(); i++)
        if ((*i).first == "Host")
            return (*i).second;
    return "";
}

HttpRequest::reqtype HttpRequest::getRequestType() const
{
    enum reqtype rt = request.first;
    return rt;
}

const std::string HttpRequest::getRequestParam() const
{
    return request.second;
}

const std::string HttpRequest::getRequestUrl() const
{
    return requestUrl;
}

const std::string HttpRequest::getHttpVersion() const
{
    return httpVersion;
}

const std::string HttpRequest::getParameter(const std::string &key) const
{
    for each (std::pair<std::string, std::string> s in paramList)
        if (s.first == key)
            return s.second;
    return "";
}

const std::string HttpRequest::getMultipartBoundary() const
{
    std::string _line = getParameter("Content-Type");
    int pos;

    if (_line == "")
        return "";
    pos = strpos(_line.c_str(), "boundary=", _line.length());
    return _line.substr(pos + 9);
}

void HttpRequest::evalCookies(const std::string &cookieString)
{
	std::list<std::string> cookies = string_split(cookieString, ';');
	for (auto i = cookies.cbegin(); i != cookies.cend(); i++)
	{
		size_t pos = (*i).find('=');
		std::string key = (*i).substr(1, pos -1);
		std::string value = (*i).substr(pos +1);
		cookieMng.setInitValue(key, value);
	}
}

CookieManager *HttpRequest::getCookies()
{
	return &cookieMng;
}
