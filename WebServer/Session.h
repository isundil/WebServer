#pragma once

#include <map>
#include <string>

class Session
{
public:
    Session();
    ~Session();

    template <class E>
    E getValue(const std::string &name)
    {
        std::string value = values.at(name);
        std::stringstream ss;
        ss.str(value);
        E result;
        ss >> result;
        return result;
    }

    template <class E>
    E getValue(const std::string &name, E defaultValue)
    {
        std::string value;
        try
        {
            value = values.at(name);
        }
        catch (std::exception &e)
        {
            (void) e;
            return defaultValue;
        }
        std::stringstream ss;
        ss.str(value);
        E result;
        ss >> result;
        return result;
    }

    template <class E>
    Session *setValue(const std::string &name, E value)
    {
        std::stringstream ss;
        ss << value;
        if (!value_exists(name))
            values[name] = ss.str();
        else
            values[name] = ss.str();
        return this;
    }
    void setDefaultExpire(const time_t &expire);
    time_t getDefaultExpire() const;
    bool value_exists(const std::string &name) const;
    void destroy(const std::string &name);
    void clear();
    void updateTime();
    time_t getExpire() const;
    void * storage(void * storage = NULL);

private:
    std::map<const std::string, std::string> values;
    time_t expire;
    time_t destroyAt;
    void * _storage;
};
