#pragma once

#include <map>
#include <string>
#include <sstream>

class CookieManager
{
public:
	CookieManager();
	~CookieManager();

	template <class E>
	E getValue(const std::string &name)
	{
		std::string value = cookies[name];
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
			value = cookies.at(name);
		}
		catch (std::exception &e)
		{
			return defaultValue;
		}
		std::stringstream ss;
		ss.str(value);
		E result;
		ss >> result;
		return result;
	}

	template <class E>
	CookieManager *setValue(const std::string &name, E value)
	{
		std::stringstream ss;
		ss << value;
		cookies[name] = ss.str();
		return this;
	}

	void debug() const;

private:
	std::map<std::string, std::string> cookies;
};

