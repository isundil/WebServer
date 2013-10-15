#pragma once

#include <map>
#include "WebServer.hpp"

class CookieManager;
class HttpRequest;
class Response;
class Session;

/*!
* This class represents a http client which do a request.
* An valid instance of this class will be passed to requested
* instance of AWebPage. You can use this class to interract whith the
* remote client browser
*/
class HttpClient
{
public:
    /*!
    * Create an httpClient using socket.
    * socket will be used to send the response
    */
    HttpClient(WebServer::ClientSocket *sock);
    /*!
    * Destroy the client, closing the socket
    */
    virtual ~HttpClient();

    /*!
    * Parse the param given as parameter, and add it to the
    * http request header (input)
    */
    bool addParam(const std::string & param);
    /*!
    * Print several infos on stdout.
    * SHOULD NOT be used outside a debug environment.
    */
    void debug() const;

    /*!
    * Attach a server to the current client.
    */
    HttpClient *setServer(WebServer *srv);
    /*!
    * return the attached server.
    */
    const WebServer *getServer() const;
    /*!
    * Return the http request header.
    * Can be used to get informations about the request
    */
    HttpRequest * getRequest() const;

    /*!
    * return the cookies set of the client.
    * This object can be used to add, modify, and delete cookies.
    */
    CookieManager * getCookies();

    /*!
    * Add an extra field to the http response header
    */
    HttpClient * addHeader(const std::string &key, const std::string & value);
    /*!
    * Return the response code, as string
    * (ex: 404 => "Document not found"
    */
    std::string getRespondStringCode(unsigned short code);
    /*!
    * Send the response to the client
    * SHOULD NOT be used outside the WebServer class
    */
    void sendResponse();
    /*!
    * Get or Set the response code (ex: 404 -> document not found).
    * If a parameter is given, the response code will be replaced by this value.
    * Return the (new ?) response code.
    */
    int respondCode(int respondCode = -1);

    /*!
    * Read the next header parameter, using socket::readLine, and
    * add it to the request parameters
    */
    bool readNextParam();

    /*!
    * Return the client socket.
    * use it if you want to know, for example, the client's ip or port.
    */
    const WebServer::ClientSocket * getConstSocket() const;

    /*!
    * Return the user's session.
    * If it does not exists, return NULL
    */
    Session * sessionGetOrNull();
    /*!
    * Return the user's session.
    * If it does not exists, create it then return it
    */
    Session * sessionGetOrCreate();
    /*!
    * Destroy the user session, and ask the client to remove the cookie
    * sessid.
    */
    void sessionDestroy();
    /*!
    * Return the response document
    */
    Response * responseGet();
    /*!
    * Return the response document
    */
    const Response * responseGetConst() const;

private:
    /*!
    * The client's socket
    */
    WebServer::ClientSocket * getSocket() const;
    /*!
    * Return the response document length
    */
    unsigned int getRespondSize();
    /*!
    * Update the sessions, removing all the expired one
    */
    void sessionUpdate();

private:
    /*!
    * The client's socket
    */
    WebServer::ClientSocket * const socket;
    /*!
    * The associated server
    */
    WebServer *server;
    /*!
    * the html response header
    */
    std::map<std::string, std::string> header;
    /*!
    * The html request header
    */
    HttpRequest *req;
    /*!
    * reponse code (ex: 404)
    */
    int responseCode;
    /*!
    * The current session (or NULL if not asked / if not exists)
    */
    Session * session;
    /*!
    * The document response
    */
    Response *response;
};
