
#include "RawRootElement.h"

RawRootElement::RawRootElement()
{
}

RawRootElement::~RawRootElement()
{
}

const std::string RawRootElement::getValue() const
{
    return value.str();
}

unsigned int RawRootElement::length() const
{
    return value.str().length();
}
