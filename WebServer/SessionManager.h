#pragma once

#include <string>
#include <map>

class Session;

/*!
* Contains all of the clients' sessions
*/
class SessionManager
{
public:
    /*!
    * return the SessionManager unique instance
    */
    static SessionManager *getInstance();

    /*!
    * return the session associated with
    * the given key, which HAVE TO be stored
    * in client-side, in a cookie
    */
    static Session * getSession(const std::string & hash);
	
    /*!
    * Create a new session, using "hash" as key
    */
    static Session * createNewSession(const std::string & hash);
    
    /*!
    * Destroy the session.
    * SHOULD NOT be used outside of the WebServer.
    * refers to HttpClient::sessionDestroy, which will also destroy
    * the cookie on client-side
    */
    static void destroy(const std::string & hash);
    
    /*!
    * Refresh the sessions, destroying all expired data
    */
    static void refresh();

private:
    /*!
    * Create the unique instance of SessionManager
    */
    SessionManager();

private:
    /*!
    * Contains the sessions, as
    * sessions[hash] = Data
    */
    std::map<const std::string, Session *> sessions;

private:
    /*!
    * Contains the unique instance of SessionManager
    */
    static SessionManager *instance;
};
