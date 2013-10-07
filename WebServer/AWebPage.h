#pragma once

#include <list>
#include "HttpRequest.h"
#include "Util.h"
#include "HtmlRootElement.h"

class HttpClient;

class AWebPage
{
public:
    virtual void requestOption  (HttpClient *client) {};
    virtual void requestGet     (HttpClient *client) {};
    virtual void requestHead    (HttpClient *client) {};
    virtual void requestPost    (HttpClient *client) {};
    virtual void requestPut     (HttpClient *client) {};
    virtual void requestDel     (HttpClient *client) {};
    virtual void requestTrace   (HttpClient *client) {};
    virtual void requestConnect (HttpClient *client) {};

protected:
    html::HtmlRootElement * const root;

public: // public route function to override
    virtual int  operator==     (const HttpRequest &request)
    {
        auto requestType = this->getRequestType();
        bool requestTypeMatch = false;
        for (auto i = requestType.cbegin(); i != requestType.cend(); i++)
            if ((*i) == request.getRequestType())
            {
                requestTypeMatch = true;
                break;
            }
        if (!requestTypeMatch)
            return false;
        return urlMatch(request.getRequestUrl(), this->getRequestUrl());
    };

    virtual std::list<enum HttpRequest::reqtype> getRequestType()
    {
        std::list<enum HttpRequest::reqtype> list;
        list.push_back(HttpRequest::reqtype::post);
        list.push_back(HttpRequest::reqtype::get);
        return list;
    }

    virtual const std::string getRequestUrl()
    {
        return "/";
    }

public:
    AWebPage(): root(new html::HtmlRootElement()) {};

private:
    bool urlMatch(const std::string & requestUrl, const std::string &myUrl)
    {
        std::list<const std::string> reqUrlList = string_split(requestUrl, '/');
        std::list<const std::string> routeUrlList = string_split(myUrl, '/');
        int len = routeUrlList.size();

        auto a = reqUrlList.cbegin();   //const iterator
        auto b = routeUrlList.cbegin(); //const iterator

        for (true; a != reqUrlList.cend() && b != routeUrlList.cend(); true)
        {
            while (a != reqUrlList.cend() && (*a).size() == 0)
                a++;
            while (b != routeUrlList.cend() && (*b).size() == 0)
                b++;
            if (a == reqUrlList.cend() && b == routeUrlList.cend())
                return true;
            if ((a == reqUrlList.cend() || b == routeUrlList.cend()) ||
                ((*b).size() == 0 || (*a).size() == 0) ||
                ((*b).at(0) != '$' && *b != *a))
                return false;
            a++;
            b++;
        }
        return true;
    }
};
