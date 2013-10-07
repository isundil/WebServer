#pragma once

#include <map>

class Session
{
public:
    Session();
    ~Session();

private:
    std::map<const std::string, std::string> values;
};