#pragma once
#include <string>

class ARootElement
{
public:
    virtual const std::string getValue() = 0;
    virtual unsigned int length() =0 ;
};
