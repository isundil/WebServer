#pragma once
#include "AHtmlNode.h"
#include "HttpRequest.h"

class FileInputData;
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
        class FileField;
        template <typename T>class ABasicInput;

    public:
        Form(const std::string & name, enum HttpRequest::reqtype = HttpRequest::post, const std::string &action = "#");
        Form(const Form &other, const std::map<std::string, std::string> &values, const std::map<std::string, FileInputData *> &files);
        Form(const Form &other);
        virtual ~Form();

        Form &actionSet(const std::string &url);
        std::string actionGet() const;

        Form &methodSet(enum HttpRequest::reqtype = HttpRequest::post);
        enum HttpRequest::reqtype methodGet() const;

        AHtmlNode *getChild(const std::string &name) const;
        const std::map<std::string, const AInput *>getValues() const;

        std::string debug() const;

        std::string getFormName() const;
        virtual const std::string toString();
    };
}
