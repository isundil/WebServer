#pragma once
#include <sstream>
#include "ARootElement.h"

class RawRootElement : public ARootElement
{
public:
    RawRootElement();
    template <class T>
    RawRootElement(T elem)
    {
        value << elem;
    }
    virtual ~RawRootElement();
    virtual const std::string getValue();
    virtual unsigned int length();

private:
    std::stringstream value;
};
