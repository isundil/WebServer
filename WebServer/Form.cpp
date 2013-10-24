#include "Form.h"
#include "hiddenField.h"

using namespace html;

Form::Form(const std::string &name) : Form("#", HttpRequest::post)
{
    *this << new Form::HiddenField("name", name);
}

Form::Form(const std::string &act, enum HttpRequest::reqtype type)
{
    actionSet(act).methodSet(type);
    canHaveChildren = true;
    canHaveStyle = true;
    name = "form";
}

Form::Form(const Form &other) : Form(other.actionGet(), other.methodGet())
{
    for (auto i = other.getChildren().cbegin(); i != other.getChildren().cend(); i++)
    {
        Form::AInput *input = dynamic_cast<html::Form::AInput *>(*i);
        if (input != NULL)
            *this << input->clone();
    }
}

Form::Form(const Form &other, const std::map<std::string, std::string> values) : Form(other)
{
    Form::AInput *in;
    std::string name;
    std::map<std::string, std::string>::const_iterator value;

    for (auto i = getChildren().cbegin(); i != getChildren().cend(); i++)
    {
        in = dynamic_cast<Form::AInput *> (*i);
        if (!in)
            continue;
        name = in->inputName();
        value = values.find(name);
        if (value == values.cend())
            continue;
        in->setString((*value).second);
    }
}

Form::~Form()
{
}

Form::AInput * Form::getChild(const std::string &name) const
{
    for (auto i = this->getChildren().cbegin(); i != getChildren().cend(); i++)
    {
        AInput * _i = dynamic_cast<AInput *> (*i);
        if (_i == NULL)
            continue;
        if (_i->inputName() == name)
            return _i;
    }
    return NULL;
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
