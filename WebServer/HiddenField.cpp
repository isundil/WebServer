#include "hiddenField.h"

html::Form::HiddenField::HiddenField(const std::string &_name, const std::string &_value) : AInput("hidden", _name)
{
    value(_value);
}

html::Form::HiddenField::HiddenField() : AInput("hidden")
{ }

html::Form::HiddenField::~HiddenField()
{ }

std::string html::Form::HiddenField::value() const
{
    return attributeGet("value");
}

std::string html::Form::HiddenField::value(const std::string &value)
{
    attributeAdd("value", value);
    return value;
}

void html::Form::HiddenField::setString(const std::string &in)
{
    this->value(in);
}

html::Form::HiddenField *html::Form::HiddenField::clone() const
{
    html::Form::HiddenField *result = new html::Form::HiddenField(*this);
    result->name = name;
    result->inputName(inputName());
    result->value(value());
    return result;
}

const std::string html::Form::HiddenField::stringValue() const
{
    return value();
}
