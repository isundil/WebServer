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
		std::string value = cookies[name].first;
		std::stringstream ss;
		ss.str(value);
		E result;
		ss >> result;
		return result;
	}

	template <class E>
	E getValue(const std::string &name, E defaultValue)
	{
		std::pair<std::string, bool> value;
		try
		{
			value = cookies.at(name);
		}
		catch (std::exception &e)
		{
			return defaultValue;
		}
		std::stringstream ss;
		ss.str(value.first);
		E result;
		ss >> result;
		return result;
	}

	template <class E>
	CookieManager *setValue(const std::string &name, E value)
	{
		isWritting = true;
		std::stringstream ss;
		ss << value;
		cookies[name] = std::pair<std::string, bool> (ss.str(), true);
		return this;
	}

	std::string getString() const;
	void debug() const;

	bool hasNew() const;

private:
	std::map<std::string, std::pair<std::string, bool> > cookies;
	bool isWritting;
};

