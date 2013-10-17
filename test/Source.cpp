#include <iostream>
#include <string>
#include <time.h> //init rand()
#include "../WebServer/WebServer.hpp"
#include "../WebServer/AWebPage.h"
#include "../WebServer/HttpClient.h"
#include "../WebServer/HttpRequest.h"
#include "../WebServer/SocketException.h"
#include "../WebServer/Session.h"
#include "../WebServer/Response.h"
#include "../WebServer/RawRootElement.h"

class SessionData
{
public:
    SessionData(const std::string & val) : data(val) {};
    ~SessionData() {};
    const std::string getValue() const
    {
        return data;
    }

private:
    const std::string data;
};

class IndexPage : public AWebPage
{
    void requestGet(HttpClient *client)
    {
		client->getCookies()->setValue("a", 42)->setValue("test_string", "coucou les gens");
        client->getCookies()->destroy("bbec");
        bool s = client->sessionGetOrNull() == NULL;
		Session * sess = client->sessionGetOrCreate();
        Response * re = client->responseGet();

		std::string sessions[8] = { "Annie", "Arielle", "Anna", "Camille", "Coralie", "Caroline", "Cyntia", "Cyndie" };
        if (sess->storage() == NULL)
            sess->storage(new SessionData(sessions[rand() % 8]));
        //re->setElement(new RawRootElement("<!DOCTYPE html><html><body><h1>test</h1><p>test " +((SessionData *)sess->storage())->getValue() +"</p></body></html>\n"));
        html::HtmlRootElement * htmlRoot = new html::HtmlRootElement("Example page");
        re->setElement(htmlRoot);
        htmlRoot->addScript("test.js").addStyle("test.css").addScript("script2.js");
        //if (!s)
        //    client->sessionDestroy();
    }

    void requestPost(HttpClient * client)
    {
        const std::string result = "BAAAAAAH";
        client->responseGet()->setElement(new RawRootElement(result));
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
    ws->registerDirectory("D:/", "/public/", true, true);
    ws->registerDirectory("D:/Project/WebServer/WebServer/", "/public/ws/", true, true);

    ws->start();
	delete ws;
}
