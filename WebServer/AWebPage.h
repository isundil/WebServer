#pragma once

#include <list>
#include "HttpRequest.h"
#include "Util.h"
#include "HtmlRootElement.h"


class HttpClient;
class AWebPage;
namespace html
{
    class Form;
}
typedef void (AWebPage::*AWebPageRequestHandler)(HttpClient *);

/*!
* Describe a route. AWebPage MUST be used to register a route
* You have to override at least ONE OF the requestTYPE method below,
* and call WebServer::registerRoute<AN_INSTANCE_OF_AWEBPAGE>();,
* where AN_INSTANCE_OF_AWEBPAGE is your implementation of your
* web page.
* You also HAVE TO override (getRequestUrl AND getRequestType (not mendatory))
* OR operator== to check if you webPage has to be called be the current client.
*/
class AWebPage
{
public:
    /*!
    * Called on an OPTION query
    */
    virtual void requestOption  (HttpClient *client) { (void) client; };
    /*!
    * Called on an GET query
    */
    virtual void requestGet(HttpClient *client) { (void) client; };
    /*!
    * Called on an HEAD query
    */
    virtual void requestHead(HttpClient *client) { (void) client; };
    /*!
    * Called on an POST query
    */
    virtual void requestPost(HttpClient *client) { (void) client; };
    /*!
    * Called on an PUT query
    */
    virtual void requestPut(HttpClient *client) { (void) client; };
    /*!
    * Called on an DEL query
    */
    virtual void requestDel(HttpClient *client) { (void) client; };
    /*!
    * Called on an TRACE query
    */
    virtual void requestTrace(HttpClient *client) { (void) client; };
    /*!
    * Called on an CONNECT query
    */
    virtual void requestConnect(HttpClient *client) { (void) client; };

public: // public route function to override
    /*!
    * Called to check if the requested route match this document
    */
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

    /*!
    * Return the available HTTP VERB for this document
    */
    virtual std::list<enum HttpRequest::reqtype> getRequestType()
    {
        std::list<enum HttpRequest::reqtype> list;
        list.push_back(HttpRequest::reqtype::post);
        list.push_back(HttpRequest::reqtype::get);
        return list;
    }

    /*!
    * Return the document's location according to the http URL (ex: "http://localhost/index.php" will match "index.php")
    * The route CAN contains variables, which will be passed to the request attribute of the HttpClient
    * (ex: http://localhost/user/toto will match "/user/$userName", and a mapped entry will contains "userName => toto")
    */
    virtual const std::string getRequestUrl()
    {
        return "/";
    }

    /*!
    * Select the good request type, and call it
    */
    void requestHandler(HttpRequest::reqtype type, HttpClient * client);

public:
    /*!
    * Init internal attributes
    */
    AWebPage();
    /*!
    * Destroy the object
    */
    virtual ~AWebPage();

protected:
    /*!
    * Register a form
    */
    void registerForm(html::Form * form);

private:
    /*!
    * Return true if the requestedUrl matches the current document's url
    */
    bool urlMatch(const std::string & requestUrl, const std::string &myUrl);

    std::list<html::Form *> forms;
    /*!
    * Prepare the potencial form
    */
    void prepareForm(HttpClient * client);
};
