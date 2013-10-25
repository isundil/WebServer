#pragma once
#include <list>
#include <map>
#include "ARootElement.h"

class JsonRootElement : public ARootElement
{
public:
    JsonRootElement();
    JsonRootElement(const std::list<std::string> &value);
    JsonRootElement(const std::map<std::string, std::string> &value);
    virtual ~JsonRootElement();

    JsonRootElement &setValue(const std::list<std::string> &value);
    JsonRootElement &setValue(const std::map<std::string, std::string> &value);

    const std::string getValue();
    unsigned int length();

private:
    std::string result;
};

