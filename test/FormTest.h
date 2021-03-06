#pragma once
#include <string>
#include "../WebServer/AWebPage.h"
#include "../WebServer/HtmlRootElement.h"
#include "../WebServer/Form.h"
#include "../WebServer/HttpClient.h"
#include "../WebServer/Response.h"
#include "../WebServer/hiddenField.h"
#include "../WebServer/SubmitButton.h"
#include "../WebServer/TextBox.h"
#include "../WebServer/PasswordBox.h"
#include "../WebServer/RawRootElement.h"
#include "../WebServer/FileField.h"

class FormTest: public AWebPage
{
public:
    FormTest()
    {
        f = new html::Form(std::string("test"), HttpRequest::get);
        a1 = new html::Form::HiddenField("a1", "b1");
        a2 = new html::Form::HiddenField("a2", "b2");
        a3 = new html::Form::HiddenField("a3", "b3");
        file = new html::Form::FileField("testFile");
        username = new html::Form::TextBox("username");
        password = new html::Form::PasswordBox("password");
        btSend = new html::Form::SubmitButton("Send the pat&eacute;");

        *f << a1 << a2 << a3 << username << password << btSend;

        registerForm(f);
    }

    ~FormTest()
    {
        delete f;
        delete a1;
        delete a2;
        delete a3;
        delete username;
        delete password;
        delete file;
        delete btSend;
    }

    const std::string getRequestUrl()
    {
        return "/testForm";
    }

    void requestGet(HttpClient * c)
    {
        if (c->getForm() != nullptr)
            return requestPost(c);
        html::HtmlRootElement *h = new html::HtmlRootElement();

        *h << f;

        c->responseGet()->setElement(h);
    }

    void requestPost(HttpClient *c)
    {
        RawRootElement *e;
        html::Form *form = c->getForm();

        if (!form)
            return;
        e = new RawRootElement(form->debug());

        //html::Form::FileField *f = (html::Form::FileField *)(form->getChild("testFile"));
        //f->data()->save(((html::Form::TextBox *)(form->getChild("username")))->stringValue());

        c->responseGet()->setElement(e);
    }

private:
    html::Form *f;

    html::Form::HiddenField *a1;
    html::Form::HiddenField *a2;
    html::Form::HiddenField *a3;
    html::Form::TextBox *username;
    html::Form::PasswordBox *password;
    html::Form::SubmitButton *btSend;
    html::Form::FileField *file;
};
