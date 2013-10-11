#pragma once

#include <map>
#include <string>
#include <sstream>

class CookieManager
{
private: //private nested
    class Data
    {
    public:
        Data(const std::string & value, bool isNew, time_t expire);
        ~Data();

        time_t getExpire() const;
        void setExpire(const time_t &value);
        std::string getValue() const;
        void setValue(const std::string &);
        bool isModified() const;

    private: //private attributes
        std::string value;
        bool isWritten;
        time_t expire;
    };

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
		std::string value;
		try
		{
			value = cookies.at(name)->getValue();
		}
		catch (std::exception &e)
		{
            (void) e;
			return defaultValue;
		}
		std::stringstream ss;
		ss.str(value);
		E result;
		ss >> result;
		return result;
	}

    template <class E>
    CookieManager *setValue(const std::string &_name, E value)
    {
        return this->setValue(_name, value, time(NULL) + defaultExpire);
    }

    template <class E>
    CookieManager *setValue(const std::string &_name, E value, time_t expire)
    {
        std::string name(_name);
        prepareName(name);
        isWritting = true;
        std::stringstream ss;
        ss << value;
        if (!cookie_exists(name))
            cookies[name] = new Data(ss.str(), true, time(NULL) + defaultExpire);
        else
            cookies[name]->setValue(ss.str());
        return this;
    }

	void setInitValue(const std::string &key, const std::string &value);

	std::string getString() const;
	void debug() const;
    void destroy(const std::string & name);
    bool cookie_exists(const std::string & name) const;
	bool hasNew() const;
    void setDefaultExpireTime(time_t time);
    void updateExpire(const std::string &name, const time_t &expire);

private: //private methods
	void prepareName(std::string &);

private: //private attributes
	std::map<std::string, Data *> cookies;
	bool isWritting;
    time_t defaultExpire;
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
