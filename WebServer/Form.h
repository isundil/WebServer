#pragma once
#include "AHtmlNode.h"
#include "HttpRequest.h"

class AWebPage;
class HttpClient;

namespace html
{
    class Form: public AHtmlNode
    {
    public: //public nested
        class AInput;
        class HiddenField;
        class SubmitButton;
        class TextBox;
        class PasswordBox;
        template <typename T>class ABasicInput;

    public:
        Form(const std::string & name);
        Form(const std::string & url, enum HttpRequest::reqtype);
        Form(const Form &other, const std::map<std::string, std::string> values);
        Form(const Form &other);
        virtual ~Form();

        Form &actionSet(const std::string &url);
        std::string actionGet() const;

        Form &methodSet(enum HttpRequest::reqtype = HttpRequest::post);
        enum HttpRequest::reqtype methodGet() const;

        AInput *getChild(const std::string &name) const;
        const std::map<std::string, const AInput *>getValues() const;

        std::string debug() const;
    };
}
