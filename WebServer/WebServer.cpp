#include <iostream>
#include "WebServer.hpp"
#include "HttpClient.h"
#include "HttpRequest.h"
#include "AWebPage.h"
#include "HttpError.h"
#include "Response.h"

WebServer::WebServer(unsigned int port) : listeningPort(port)
{
    socket = new WebServer::Socket(listeningPort);
}

WebServer::~WebServer()
{
    delete socket;
}

std::string WebServer::getWebmaster() const
{
    return webMaster;
}

WebServer * WebServer::setWebmaster(const std::string & newMail)
{
    webMaster = newMail;
    return this;
}

void WebServer::start()
{
    while (true)
    {
        HttpClient * client = socket->waitForRequest();
        client->setServer(this);
        try {
            newClient(client);
        }
        catch (InvalidRequestException &e) {
            (void) e;
        }
        catch (HttpError &e) {
            HttpError *ptr = &e;
            if (dynamic_cast<Error403 *>(ptr) != NULL)
                client->respondCode(403);
            else if (dynamic_cast<Error404 *>(ptr) != NULL)
                client->respondCode(404);
        }
        //catch (std::exception &e)
        //{
        //    (void) e;
        //    //TODO replace client response
        //    client->respondCode(500);
        //}
        try {
            client->sendResponse();
        }
        catch (std::exception &e)
        {
            (void) e;
            std::cerr << "Cannot send response" << std::endl;
        }
        delete client;
    }
}

void WebServer::newClient(HttpClient *client)
{
    while (client->readNextParam());
    client->getRequest()->debug();
    execRequest(client);
}

void WebServer::execRequest(HttpClient *client)
{
    if (!client->getRequest()->isValid())
        throw InvalidRequestException();
    for (auto i = routes.begin(); i != routes.end(); i++)
        if (*(*i) == *(client->getRequest()))
            return (*i)->requestHandler(client->getRequest()->getRequestType(), client); //TODO other requests types
    if (client->getRequest()->getRequestType() == HttpRequest::reqtype::get)
        for (auto i = mappedDirectories.cbegin(); i != mappedDirectories.cend(); i++)
        {
            std::string real;
            if ((real = (*i)->match(client->getRequest()->getRequestUrl())) != "")
                return sendFile(real, client);
        }
    throw Error404();
}

void WebServer::sendFile(const std::string & path, HttpClient * cli)
{
    FileElement * elem = new FileElement(path);
    cli->responseGet()->setElement(elem);
    cli->sendResponseHeader();
    elem->send(cli->getSocket());
}

void WebServer::registerDirectory(const std::string & path, const std::string & url, bool recursive)
{
    mappedDirectories.push_back(new WebServer::MappedDirectory(path, url, recursive));
}
