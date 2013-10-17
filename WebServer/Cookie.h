#pragma once

#include <map>
#include <string>
#include <sstream>

/*!
* Describes all of the client's cookies, at the query time
* None of the cookies are stored on the server, refers to
* Session if you want server-side stored data
*/
class CookieManager
{
private: //private nested
    /*!
    * Contains one Cookie value.
    * Can indicate if this value is new or not,
    * And its expiration time.
    */
    class Data
    {
    public:
        /*!
        * Create a new Data. SHOULD NOT be used outside of the CookieManager class.
        * indicate the value as string, if the cookie is new and the expiration time.
        */
        Data(const std::string & value, bool isNew, time_t expire);
        ~Data();

        /*!
        * return the expiration time
        */
        time_t getExpire() const;

        /*!
        * set the expiration time
        */
        Data &setExpire(const time_t &value);

        /*!
        * return the cookie's value
        */
        std::string getValue() const;

        /*!
        * set the cookie's value
        */
        Data &setValue(const std::string &);

        /*!
        * return true if the cookie has to be sent to the client
        * (if new or modified)
        */
        bool isModified() const;

    private: //private attributes
        /*!
        * cookie's value
        */
        std::string value;

        /*!
        * Is cookie new ?
        */
        bool isWritten;

        /*!
        * cookie's expire time
        */
        time_t expire;
    };

public:
	CookieManager();
	~CookieManager();

    /*!
    * return the value. Call this function as
    * DesiredType d = CookieManager->getValue<DesiredType>(name)
    * Throw an "OutOfRange Exception if value does not exists
    */
	template <class E>
	E getValue(const std::string &name)
	{
		std::string value = cookies.at(name)->getValue();
		std::stringstream ss;
		ss.str(value);
		E result;
		ss >> result;
		return result;
	}

    /*!
    * return the value. Call this function as
    * DesiredType d = CookieManager->getValue<DesiredType>(name, (DesiredType) defaultValue)
    * return defaultValue if not exists
    */
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

    /*!
    * set the value. If it does not exists, create a new Cookie
    * use default expire date.
    */
    template <class E>
    CookieManager *setValue(const std::string &_name, E value)
    {
        return this->setValue(_name, value, time(NULL) + defaultExpire);
    }

    /*!
    * set the value. If it does not exists, create a new Cookie
    * Use the expire date given as parameter
    */
    template <class E>
    CookieManager *setValue(const std::string &_name, E value, time_t expire)
    {
        std::string name(_name);
        prepareName(name);
        isWritting = true;
        std::stringstream ss;
        ss << value;
        if (!cookie_exists(name))
            cookies[name] = new Data(ss.str(), true, expire);
        else
            cookies[name]->setValue(ss.str()).setExpire(expire);
        return this;
    }

    /*!
    * Create a new Cookie, and set it as old
    * To be used ONLY for cookies given by the client
    * SHOULD NOT be used outside the WebServer internal
    */
    void setInitValue(const std::string &key, const std::string &value);

    /*!
    * Destroy the cookie given by "name"
    * Ask for the client to delete it
    */
    void destroy(const std::string & name);

    /*!
    * return the http header field containing new cookies
    */
    std::string getString() const;

    /*!
    * Return true if there is a cookie associated with "name"
    */
    bool cookie_exists(const std::string & name) const;

    /*!
    * Return true if the client have to be noticed of a new cookie
    */
    bool hasNew() const;

    /*!
    * Set the default expire time of all new cookies
    */
    void setDefaultExpireTime(time_t time);

    /*!
    * update the expire time of a cookie.
    * if expire < now, then the cookie will be destroyed by the client
    */
    void updateExpire(const std::string &name, const time_t &expire);

private: //private methods
    /*!
    * check if the name is valid. Throw a InvalidNameException
    */
    void prepareName(std::string &);

private: //private attributes
    /*!
    * The cookies, as cookies[name] = data
    */
    std::map<std::string, Data *> cookies;

    /*!
    * true if there are new cookies, or if the client have to be
    * noticed of any changes on his cookies
    */
    bool isWritting;

    /*!
    * contains the default expire interval of time
    * of a new cookie
    */
    time_t defaultExpire;
};

/*!
* Exception of invalid name or value
* Supposedly, a name is invalid if it contains
* a '"' character inside it
*/
class InvalidNameException: public std::exception
{
public:
    /*!
    * Constructor. the name contains the invalid name to report.
    */
    InvalidNameException(const std::string &name) : _name(name)
    {}
    virtual ~InvalidNameException()
    {}

    /*!
    * Return the error description
    */
	const char * what() const throw ()
	{
		return std::string("Invalid name: "+_name).c_str();
	}

private:
    /*!
    * The invalid name to report.
    */
	const std::string &_name;
};
