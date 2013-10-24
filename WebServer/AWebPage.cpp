#include <string>
#include "AWebPage.h"
#include "Form.h"
#include "HttpClient.h"
#include "AInput.h"
#include "hiddenField.h"

using namespace html;

AWebPage::AWebPage()
{
}

AWebPage::~AWebPage()
{
}

void AWebPage::prepareForm(HttpClient *client)
{
    std::string name;
    
    try
    {
        name = client->getPostData().at("name");
    }
    catch (std::out_of_range &e)
    {
        return;
    }

    for (auto i = forms.begin(); i != forms.end(); i++)
    {
        Form::HiddenField *c = dynamic_cast<Form::HiddenField *> ((*i)->getChild("name"));
        if (c != NULL && c->value() == name)
        {
            client->setForm(*i);
            return;
        }
    }
}

void AWebPage::requestHandler(HttpRequest::reqtype type, HttpClient * client)
{
    AWebPageRequestHandler ptrs[9];

    ptrs[HttpRequest::option] = &AWebPage::requestOption;
    ptrs[HttpRequest::get] = &AWebPage::requestGet;
    ptrs[HttpRequest::head] = &AWebPage::requestHead;
    ptrs[HttpRequest::post] = &AWebPage::requestPost;
    ptrs[HttpRequest::put] = &AWebPage::requestPut;
    ptrs[HttpRequest::del] = &AWebPage::requestDel;
    ptrs[HttpRequest::trace] = &AWebPage::requestTrace;
    ptrs[HttpRequest::connect] = &AWebPage::requestConnect;
    prepareForm(client);
    (this->*ptrs[type])(client);
}

bool AWebPage::urlMatch(const std::string & requestUrl, const std::string &myUrl)
{
    std::list<std::string> reqUrlList = string_split(requestUrl, '/');
    std::list<std::string> routeUrlList = string_split(myUrl, '/');

    auto a = reqUrlList.cbegin();   //const iterator
    auto b = routeUrlList.cbegin(); //const iterator

    for (; a != reqUrlList.cend() && b != routeUrlList.cend();)
    {
        while (a != reqUrlList.cend() && (*a).size() == 0)
            a++;
        while (b != routeUrlList.cend() && (*b).size() == 0)
            b++;
        if (a == reqUrlList.cend() && b == routeUrlList.cend())
            return true;
        if ((a == reqUrlList.cend() || b == routeUrlList.cend()) ||
            ((*b).size() == 0 || (*a).size() == 0) ||
            ((*b).at(0) != '$' && *b != *a))
            return false;
        a++;
        b++;
    }
    return true;
}

void AWebPage::registerForm(html::Form * form)
{
    forms.push_back(form);
}
