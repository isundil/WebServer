#include <iostream>
#include "Cookie.h"

CookieManager::CookieManager()
{
	isWritting = false;
}

CookieManager::~CookieManager()
{
}

void CookieManager::debug() const
{
    for (auto i = cookies.cbegin(); i != cookies.cend(); i++)
        std::cout << "{" << (*i).first << "} => {" << (*i).second.first << "}" << std::endl;
}

std::string CookieManager::getString() const
{
	std::stringstream result;

    for (auto i = cookies.cbegin(); i != cookies.cend(); i++)
		if ((*i).second.second == true)
			result << "Set-Cookie: " << (*i).first << "=" << (*i).second.first << std::endl;
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
	cookies[key] = std::pair<std::string, bool>(value, false);
}

void CookieManager::prepareName(std::string &name)
{
	for (const char * str = name.c_str(); *str; str++)
		if (!((*str >= 'a' && *str <= 'z') || (*str >= 'A' && *str <= 'Z') || (*str >= '0' && *str <= '9') || *str == '_'))
			throw InvalidNameException(name);
}
