#include "../WebServer/WebServer.hpp"
#include "../WebServer/AWebPage.h"
#include "../WebServer/HttpClient.h"
#include "../WebServer/HttpRequest.h"

class IndexPage : public AWebPage
{
    void requestGet(HttpClient *client)
    {
        client->debugResponse = ("<!DOCTYPE html><html><body><h1>test</h1><p>test blablabla</p></body></html>");
    }

    const std::string getRequestUrl()
    {
        return "/";
    }
};

int main(int ac, char **av)
{
    WebServer ws = WebServer(8080);

    ws.registerRoute<IndexPage>();

    ws.start();
}
