#include <iostream>
#include "Cookie.h"

CookieManager::CookieManager()
{
}

CookieManager::~CookieManager()
{
}

void CookieManager::debug() const
{
    for (auto i = cookies.cbegin(); i != cookies.cend(); i++)
        std::cout << "{" << (*i).first << "} => {" << (*i).second << "}" << std::endl;
}

