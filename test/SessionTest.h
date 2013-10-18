#pragma once

#include "../WebServer/AWebPage.h"
#include "../WebServer/JsonRootElement.h"

class SessionTest : public AWebPage
{
    void requestGet(HttpClient *c)
    {
        Session *s = c->sessionGetOrCreate();

        c->responseGet()->setElement(new JsonRootElement(s->getMap()));
    }

    const std::string getRequestUrl()
    {
        return "/sessionTest";
    }
};
