#include <time.h>
#include "SessionManager.h"
#include "Session.h"

SessionManager *SessionManager::getInstance()
{
    if (SessionManager::instance == NULL)
        SessionManager::instance = new SessionManager();
    return SessionManager::instance;
}

SessionManager::SessionManager()
{
}

Session * SessionManager::getSession(const std::string & hash)
{
	try {
		return SessionManager::getInstance()->sessions.at(hash);
	}
	catch (std::exception &e)
	{
        (void) e;
	}
	return NULL;
}

Session * SessionManager::createNewSession(const std::string & hash)
{
    Session *newSession = new Session();
    SessionManager::getInstance()->sessions[hash] = newSession;
	return newSession;
}

void SessionManager::destroy(const std::string & hash)
{
    SessionManager::getInstance()->sessions.erase(SessionManager::getInstance()->sessions.find(hash));
}

void SessionManager::refresh()
{
    auto i = SessionManager::getInstance()->sessions.begin();
    time_t now = time(NULL);

    while (i != SessionManager::getInstance()->sessions.end())
    {
        if ((*i).second->getExpire() < now)
        {
            SessionManager::destroy((*i).first);
            return SessionManager::refresh();
        }
        i++;
    }
    return;
}

SessionManager *SessionManager::instance = NULL;
