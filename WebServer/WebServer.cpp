#include <fstream>
#include <iostream>
#include "WebServer.hpp"
#include "HttpClient.h"
#include "HttpRequest.h"
#include "AWebPage.h"
#include "HttpError.h"
#include "Response.h"
#include "DirContentRootElem.h"
#include "RawRootElement.h"
#include "config.h"

WebServer::WebServer(unsigned int port) : listeningPort(port)
{
    socket = new WebServer::Socket(listeningPort);
    mimeList = initMimeType(CONF_DIR""MIME_CONFFILE);
    std::cout << "Done" << std::endl;
}

WebServer::~WebServer()
{
    delete socket;
    delete mimeList;
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
        bool haveToSend = true;
        try {
            haveToSend = newClient(client);
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
            client->responseGet()->setElement(new RawRootElement(e.what()));
            client->respondCode(500);
        }
        try {
            if (haveToSend)
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

bool WebServer::newClient(HttpClient *client)
{
    while (client->readNextParam());
    client->readData();
    //client->getRequest()->debug();
    return execRequest(client);
}

bool WebServer::execRequest(HttpClient *client)
{
    if (!client->getRequest()->isValid())
        throw InvalidRequestException();
    for (auto i = routes.begin(); i != routes.end(); i++)
        if (*(*i) == *(client->getRequest()))
        {
            (*i)->requestHandler(client->getRequest()->getRequestType(), client);
            return true;
        }
    if (client->getRequest()->getRequestType() == HttpRequest::reqtype::get)
        for (auto i = mappedDirectories.cbegin(); i != mappedDirectories.cend(); i++)
        {
            std::string real;
            bool isDirectory;
            if ((real = (*i)->match(client->getRequest()->getRequestUrl(), isDirectory)) != "")
            {
                try{
                    return sendFile(real, client, isDirectory);
                }
                catch (Error404 &e)
                {
                    (void) e;
                }
            }
        }
    throw Error404();
}

bool WebServer::sendFile(const std::string & path, HttpClient * cli, bool isDirectory)
{
    if (!isDirectory)
    {
        FileElement * elem = new FileElement(path);

        cli->responseGet()->setElement(elem);
        cli->responseGet()->setContentType(elem->getMimeType(*mimeList)); //TODO find content-mime type
        try {
            cli->sendResponseHeader();
            elem->send(cli->getSocket());
        }
        catch (std::exception &e)
        {
            (void) e;
            std::cerr << "Cannot send response" << std::endl;
        }
        return false;
    }
    //the element will be destroyed in Response::~Response so no leaks here
    cli->responseGet()->setElement(new DirContentRootElem(path, cli->getRequest()->getRequestUrl()));
    return true;
}

std::map<std::string, std::string> *WebServer::initMimeType(const std::string &filename) const
{
    std::ifstream ff(filename);
    std::string line;
    std::string::size_type pos;
    std::list<std::string> extensionList;
    std::string type;
    std::string ext;
    std::stringstream ss;
    std::map<std::string, std::string> *result = new std::map<std::string, std::string>();

    if (!ff.is_open())
        return result;

    while (!(ff.rdstate() & std::ios_base::eofbit))
    {
        std::getline(ff, line);
        if ((pos = line.find("#")) != line.npos)
            line.erase(pos, line.length());
        if (line.length() == 0)
            continue;
        ss = std::stringstream(line);
        extensionList.clear();
        ss >> type;
        while (!ss.eof())
        {
            ss >> ext;
            extensionList.push_back(ext);
        }
        //todo 1e str -> type
        //todo * str -> extensionList
        for each (auto i in extensionList)
            (*result)[i] = type;
    }
    ff.close();
    return result;
}

void WebServer::registerDirectory(const std::string & path, const std::string & url, bool recursive, bool showContent)
{
    mappedDirectories.push_back(new WebServer::MappedDirectory(path, url, recursive, showContent));
}
