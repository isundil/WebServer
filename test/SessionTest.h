#pragma once

#include <map>
#include <string>
#include "../WebServer/AWebPage.h"
#include "../WebServer/HttpClient.h"
#include "../WebServer/Session.h"
#include "../WebServer/JsonRootElement.h"

class SessionTest : public AWebPage
{
    void requestGet(HttpClient *c)
    {
        Session *s = c->sessionGetOrCreate();
        const std::map<std::string, std::string> m = s->getMap();

        c->responseGet()->setElement(new JsonRootElement(m));
    }

    const std::string getRequestUrl()
    {
        return "/sessionTest";
    }
};
