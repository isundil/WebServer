#include <time.h>
#include "Session.h"

Session::Session()
{
    expire = 60 * 60 * 1; //default expire: 1 hour
    _storage = NULL;
}

Session::~Session()
{
    this->clear();
    delete _storage;
}

time_t Session::getDefaultExpire() const
{
    return expire;
}

void Session::setDefaultExpire(const time_t & value)
{
    expire = value;
}

bool Session::value_exists(const std::string &name) const
{
    return values.find(name) == values.cend();
}

void Session::destroy(const std::string &name)
{
    values.erase(values.find(name));
}

void Session::clear()
{
    values.clear();
}

void Session::updateTime()
{
    this->destroyAt = time(NULL) + this->expire;
}

time_t Session::getExpire() const
{
    return destroyAt;
}

SessionStorage * Session::storage(SessionStorage *data)
{
    if (data)
        _storage = data;
    return _storage;
}


const std::map<std::string, std::string>Session::getMap() const
{
    return values;
}
