#include "Form.h"
#include "hiddenField.h"
#include "FileField.h"

using namespace html;

Form::Form(const std::string &name, enum HttpRequest::reqtype type, const std::string &act)
{
    *this << new Form::HiddenField("name", name);
    actionSet(act).methodSet(type);
    canHaveChildren = true;
    canHaveStyle = true;
    this->name = "form";
}

Form::Form(const Form &other) : Form(other.getFormName(), other.methodGet(), other.actionGet())
{
    Form::AInput *input;
    Form::FileField *file;

    for (auto i = other.getChildren().cbegin(); i != other.getChildren().cend(); i++)
    {
        input = dynamic_cast<html::Form::AInput *>(*i);
        file = dynamic_cast<html::Form::FileField *>(*i);
        if (input != nullptr)
            *this << input->clone();
        else if (file != nullptr)
            *this << file->clone();
    }
}

std::string Form::getFormName() const
{
    auto i = this->getChild("name");
    if (i == nullptr)
        throw std::runtime_error("noname");
    if (dynamic_cast<html::Form::HiddenField *> (i) == nullptr)
        throw std::runtime_error("noname");
    return ((Form::AInput *)i)->stringValue();
}

Form::Form(const Form &other, const std::map<std::string, std::string> &values, const std::map<std::string, FileInputData *> &files) : Form(other)
{
    Form::AInput *input;
    Form::FileField *file;
    std::string name;
    std::map<std::string, std::string>::const_iterator value;

    for each (auto i in getChildren())
    {
        input = dynamic_cast<Form::AInput *> (i);
        file = dynamic_cast<Form::FileField *> (i);

        if (input != nullptr)
        {
            name = input->inputName();
            value = values.find(name);
            if (value == values.cend())
                continue;
            input->setString((*value).second);
        }
        else if (file != nullptr)
        {
            std::map<std::string, FileInputData *>::const_iterator it;

            name = file->inputName();
            it = files.find(name);
            if (it != files.cend())
                file->data((*(files.find(name))).second);
        }
    }
}

Form::~Form()
{
}

html::AHtmlNode * Form::getChild(const std::string &name) const
{
    for (auto i = this->getChildren().cbegin(); i != getChildren().cend(); i++)
    {
        AInput * _i = dynamic_cast<AInput *> (*i);
        FileField * _f = dynamic_cast<FileField *> (*i);

        if (_i != nullptr && _i->inputName() == name)
            return _i;
        if (_f != nullptr && _f->inputName() == name)
            return _f;
    }
    return nullptr;
}

Form &Form::actionSet(const std::string &value)
{
    this->attributeAdd("action", value);
    return *this;
}

std::string Form::actionGet() const
{
    return this->attributeGet("action");
}

Form &Form::methodSet(enum HttpRequest::reqtype value)
{
    this->attributeAdd("method", HttpRequest::reqTypeToString(value));
    return *this;
}

enum HttpRequest::reqtype Form::methodGet() const
{
    return HttpRequest::stringToReqType(attributeGet("method"));
}

const std::map<std::string, const Form::AInput *> Form::getValues() const
{
    std::map<std::string, const Form::AInput *>result;
    Form::AInput *input;

    for (auto i = getChildren().cbegin(); i != getChildren().cend(); i++)
    {
        if ((input = dynamic_cast<Form::AInput *> (*i)) == NULL)
            continue;
        result.insert(std::pair<std::string, const Form::AInput *>(input->inputName(), input));
    }
    return result;
}

std::string Form::debug() const
{
    auto map = getValues();
    std::string result;
    for (auto i = map.cbegin(); i != map.cend(); i++)
        result += "{" + (*i).first + "}:{" + (*i).second->stringValue() + "}<br/>";
    return result;
}

const std::string Form::toString()
{
    for each (auto i in getChildren())
        if (dynamic_cast<Form::FileField *> (i) != nullptr)
            attributeAdd("enctype", "multipart/form-data");
    return AHtmlNode::toString();
}
