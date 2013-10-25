#include "JsonRootElement.h"

JsonRootElement::JsonRootElement()
{ }

JsonRootElement::JsonRootElement(const std::list<std::string> &value)
{
    this->setValue(value);
}

JsonRootElement::JsonRootElement(const std::map<std::string, std::string> &value)
{
    this->setValue(value);
}

JsonRootElement::~JsonRootElement()
{ }

JsonRootElement &JsonRootElement::setValue(const std::list<std::string> &value)
{
    return *this;
}

JsonRootElement &JsonRootElement::setValue(const std::map<std::string, std::string> &value)
{
    result = "{\n";
    for (auto i = value.cbegin(); i != value.cend();)
    {
        result += "\"" + (*i).first + "\": \"" + (*i).second + "\"";
        i++;
        if (i == value.cend())
            result += "\n";
        else
            result += ",\n";
    }
    result += "}";
    return *this;
}

const std::string JsonRootElement::getValue()
{
    return result;
}

unsigned int JsonRootElement::length()
{
    return result.length();
}

