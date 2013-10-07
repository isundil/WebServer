#include <iostream>
#include "WebServer.hpp"
#include "HttpClient.h"
#include "HttpRequest.h"
#include "AWebPage.h"
#include "HttpError.h"

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

WebServer * const WebServer::setWebmaster(const std::string & newMail)
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
        catch (std::exception &e)
        {
            (void) e;
            client->respondCode(500);
        }
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
    std::cout << "{" << client->getRequest()->getRequestUrl() << "}" << std::endl;
    execRequest(client);
}

void WebServer::execRequest(HttpClient *client)
{
    if (!client->getRequest()->isValid())
        throw InvalidRequestException();
    for (auto i = routes.begin(); i != routes.end(); i++)
        if (*(*i) == *(client->getRequest()))
        {
            (*i)->requestGet(client);
            return;
        }
    throw Error404();
}
