#include "BasicInput.h"

template <>
const std::string html::Form::ABasicInput<std::string>::stringValue() const
{
    return _value;
}

template <>
void html::Form::ABasicInput<std::string>::setString(const std::string &value)
{
    this->value(value);
}
