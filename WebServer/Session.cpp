#include <time.h>
#include "Session.h"

Session::Session()
{
    expire = 60 * 60 * 1; //default expire: 1 hour
}

Session::~Session()
{
    this->clear();
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
