
#include "Session.h"

Session::Session()
{
    value = "";
    expire = 60 * 60 * 1; //default expire: 1 hour
}

time_t Session::getDefaultExpire() const
{
    return expire;
}

void Session::setDefaultExpire(const time_t & value)
{
    expire = value;
}
