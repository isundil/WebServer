#include <iostream>
#include <time.h>
#include "Cookie.h"

CookieManager::CookieManager()
{
	isWritting = false;
    defaultExpire = 60 * 60 * 24; //Default cookie time: 1 day
}

CookieManager::~CookieManager()
{
    for (auto i = cookies.cbegin(); i != cookies.cend(); i++)
        delete ((*i).second);
}

void CookieManager::debug() const
{
    for (auto i = cookies.cbegin(); i != cookies.cend(); i++)
        std::cout << "{" << (*i).first << "} => {" << (*i).second->getValue() << "}" << std::endl;
}

std::string CookieManager::getString() const
{
	std::stringstream result;

    for (auto i = cookies.cbegin(); i != cookies.cend(); i++)
        if ((*i).second != NULL && (*i).second->isModified())
        {
            time_t exp = (*i).second->getExpire();
            result << "Set-Cookie: " << (*i).first << "=" << (*i).second->getValue() << "; Expires=" << ctime(&exp);
        }
	return result.str();
}

bool CookieManager::hasNew() const
{
	return isWritting;
}

void CookieManager::setInitValue(const std::string & key, const std::string & value)
{
	std::string name(key);
	prepareName(name);
    cookies[key] = new Data(value, false, defaultExpire + time(NULL));
}

void CookieManager::prepareName(std::string &name)
{
	for (const char * str = name.c_str(); *str; str++)
		if (!((*str >= 'a' && *str <= 'z') || (*str >= 'A' && *str <= 'Z') || (*str >= '0' && *str <= '9') || *str == '_'))
			throw InvalidNameException(name);
}

bool CookieManager::cookie_exists(const std::string & name) const
{
    return cookies.find(std::string(name)) != cookies.cend();
}

void CookieManager::setDefaultExpireTime(time_t expire)
{
    defaultExpire = expire;
}

void CookieManager::updateExpire(const std::string & name, const time_t &exp)
{
    CookieManager::Data *c = cookies[name];
    if (c == NULL)
        return;
    c->setExpire(exp);
}

void CookieManager::destroy(const std::string & name)
{
    CookieManager::Data *c = cookies[name];
    if (c == NULL)
        return;
    c->setExpire(0);
}

CookieManager::Data::Data(const std::string & _value, bool isNew, time_t expire)
{
    isWritten = isNew;
    value = _value;
    this->expire = expire;
}

CookieManager::Data::~Data() {}

time_t CookieManager::Data::getExpire() const
{
    return expire;
}

void CookieManager::Data::setExpire(const time_t &_value)
{
    expire = _value;
    isWritten = true;
}

std::string CookieManager::Data::getValue() const
{
    return value;
}

void CookieManager::Data::setValue(const std::string &_value)
{
    if (value == _value)
        return;
    value = _value;
    isWritten = true;
}

bool CookieManager::Data::isModified() const
{
    return isWritten;
}
