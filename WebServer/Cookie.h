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
            (void) e;
			return defaultValue;
		}
		std::stringstream ss;
		ss.str(value.first);
		E result;
		ss >> result;
		return result;
	}

	template <class E>
	CookieManager *setValue(const std::string &_name, E value)
	{
		std::string name(_name);
		prepareName(name);
		isWritting = true;
		std::stringstream ss;
		ss << value;
		cookies[name] = std::pair<std::string, bool> (ss.str(), true);
		return this;
	}

	void setInitValue(const std::string &key, const std::string &value);

	std::string getString() const;
	void debug() const;

	bool hasNew() const;

private:
	void prepareName(std::string &);

private:
	std::map<std::string, std::pair<std::string, bool> > cookies;
	bool isWritting;
};

class InvalidNameException: public std::exception
{
public:
	InvalidNameException(const std::string &name): _name(name)
	{
	}
	virtual ~InvalidNameException()
	{
	}

	const char * what() const throw ()
	{
		return std::string("Invalid name: "+_name).c_str();
	}

private:
	const std::string &_name;
};
