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

#include "SessionTest.h"
#include "FormTest.h"

class SessionData: public SessionStorage
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
        //bool s = client->sessionGetOrNull() == NULL;
		Session * sess = client->sessionGetOrCreate();
        Response * re = client->responseGet();

		std::string sessions[8] = { "Annie", "Arielle", "Anna", "Camille", "Coralie", "Caroline", "Cyntia", "Cyndie" };
        if (sess->storage() == NULL)
        {
            sess->storage(new SessionData(sessions[rand() % 8]));
            sess->setValue("name", ((SessionData *)(sess->storage()))->getValue());
        }
        re->setElement(new RawRootElement("<!DOCTYPE html><html><body><form method='post' action='#' enctype=\"multipart/form-data\"><input type=\"file\" name=\"testFile\"/><input type='submit' /></form></body></html>\n"));
        //html::HtmlRootElement * htmlRoot = new html::HtmlRootElement("Example page");
        //re->setElement(htmlRoot);
        //htmlRoot->addScript("test.js").addStyle("test.css").addScript("script2.js");
        //if (!s)
        //    client->sessionDestroy();
    }

    void requestPost(HttpClient * client)
    {
        this->requestGet(client);
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
    ws->registerRoute<SessionTest>();
    ws->registerRoute<FormTest>();
    ws->registerDirectory("/home/cafeine/projects/WebServer/", "/public/", true, true);

    ws->start();
	delete ws;
}
