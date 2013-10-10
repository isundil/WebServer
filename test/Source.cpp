#include <iostream>
#include "../WebServer/WebServer.hpp"
#include "../WebServer/AWebPage.h"
#include "../WebServer/HttpClient.h"
#include "../WebServer/HttpRequest.h"
#include "../WebServer/SocketException.h"
#include "../WebServer/SessionManager.h"

class IndexPage : public AWebPage
{
    void requestGet(HttpClient *client)
    {
        client->debugResponse = ("<!DOCTYPE html><html><body><h1>test</h1><p>test blablabla</p></body></html>\n");
		client->getRequest()->getCookies()->setValue("bbec", 42)->setValue("a", 43)->setValue("test_string", "coucou les gens");
		Session * sess = client->getOrCreateSession();
    }

    const std::string getRequestUrl()
    {
        return "/";
    }
};

int main(int ac, char **av)
{
	(void)ac; (void)av;
	WebServer *ws;
	try {
		ws = new WebServer(8080);
	}
	catch (SocketException &e)
	{
		std::cerr << "Cannot start server: " << e.what() << std::endl;
		return -1;
	}
    ws->registerRoute<IndexPage>();

    ws->start();
	delete ws;
}
