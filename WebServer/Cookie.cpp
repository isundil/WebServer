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
	bool first = true;

    for (auto i = cookies.cbegin(); i != cookies.cend(); i++)
		if ((*i).second.second == true)
		{
			if (!first)
				result << "; ";
			result << (*i).first << "=" << (*i).second.first;
			first = false;
		}
	return result.str();
}

