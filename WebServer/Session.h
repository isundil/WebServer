#pragma once

#include <map>
#include <string>

class Session
{
public:
    Session();
    ~Session();

    void setValue(const std::string &v)
    {
        value = v;
    }
    std::string getValue() const
    {
        return value;
    }
    void setDefaultExpire(const time_t &expire);
    time_t getDefaultExpire() const;

private:
    std::map<const std::string, std::string> values;
    std::string value;
    time_t expire;
};