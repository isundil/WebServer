#pragma once
#include <string>

class ARootElement
{
public:
    virtual const std::string getValue() const = 0;
    virtual unsigned int length() const =0 ;
};
