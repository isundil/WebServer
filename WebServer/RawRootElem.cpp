
#include "RawRootElement.h"

RawRootElement::RawRootElement()
{
}

RawRootElement::~RawRootElement()
{
}

const std::string RawRootElement::getValue()
{
    return value.str();
}

unsigned int RawRootElement::length()
{
    return value.str().length();
}
