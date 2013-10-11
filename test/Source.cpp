#include <iostream>
#include <time.h> //init rand()
#include "../WebServer/WebServer.hpp"
#include "../WebServer/AWebPage.h"
#include "../WebServer/HttpClient.h"
#include "../WebServer/HttpRequest.h"
#include "../WebServer/SocketException.h"
#include "../WebServer/Session.h"

class IndexPage : public AWebPage
{
    void requestGet(HttpClient *client)
    {
		client->getRequest()->getCookies()->setValue("a", 42)->setValue("test_string", "coucou les gens");
        client->getRequest()->getCookies()->destroy("bbec");
		Session * sess = client->getOrCreateSession();

        char  * sessions[8] = { "Annie", "Arielle", "Anna", "Camille", "Carolie", "Caroline", "Cyntia", "Cyndie" };
        if (sess->getValue() == "")
            sess->setValue(sessions[rand() % 8]);
        client->debugResponse = ("<!DOCTYPE html><html><body><h1>test</h1><p>test " +sess->getValue() +"</p></body></html>\n");
    }

    const std::string getRequestUrl()
    {
        return "/";
    }
};

int main(int ac, char **av)
{
    srand((int)time(NULL));
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
