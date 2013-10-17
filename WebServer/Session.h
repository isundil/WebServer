#pragma once

#include <map>
#include <string>
#include <sstream>

/*!
* Session data
*/
class Session
{
public:
    /*!
    * Create a new Session.
    * SHOULD NOT be used, see HttpClient::sessionGetOrCreate() instead
    */
    Session();
    /*!
    * Destroy the session. SHOULD NOT be used.
    * see HttpClient::sessionDestroy instead.
    */
    ~Session();

    /*!
    * Return the info contained as `key`.
    * throw an OutOfBoundException if the index does not exists
    */
    template <class E>
    E getValue(const std::string &name)
    {
        std::string value = values.at(name);
        std::stringstream ss;
        ss.str(value);
        E result;
        ss >> result;
        return result;
    }

    /*!
    * Return the info contained as `key`.
    * return defaultValue if the index does not exists
    */
    template <class E>
    E getValue(const std::string &name, E defaultValue)
    {
        std::string value;
        try
        {
            value = values.at(name);
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
    * Store the value using the `name` index.
    * E MUST BE a serializable class
    * if not, see the storage() function, or
    * override the std::stringstream::operator<<() and the 
    * std::stringstream::operator>>() method
    */
    template <class E>
    Session *setValue(const std::string &name, E value)
    {
        std::stringstream ss;
        ss << value;
        if (!value_exists(name))
            values[name] = ss.str();
        else
            values[name] = ss.str();
        return this;
    }
    /*!
    * Set the default expire date used for updating the
    * session lifetime at each request
    */
    void setDefaultExpire(const time_t &expire);
    /*!
    * Return the expire time for the session
    */
    time_t getDefaultExpire() const;
    /*!
    * check if the index `name` exists.
    * return true if it does.
    */
    bool value_exists(const std::string &name) const;
    /*!
    * Destroy the session item.
    */
    void destroy(const std::string &name);
    /*!
    * Destroy all session data
    */
    void clear();
    /*!
    * update the session lifetime
    */
    void updateTime();
    /*!
    * get the expire time of the session
    */
    time_t getExpire() const;
    /*!
    * Can be use to store custom storage inside the session.
    * SHOULD BE allocated using new(). WILL BE delete() on session
    * destructor call.
    */
    void * storage(void * storage = NULL); //TODO interface

private:
    /*!
    * the data of the session
    */
    std::map<const std::string, std::string> values;
    /*!
    * the lifetime of the session
    */
    time_t expire;
    /*!
    * The time when the session will be destroyed
    */
    time_t destroyAt;
    /*!
    * the storage area for custom objects
    */
    void * _storage;
};
