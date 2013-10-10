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
	}
	return NULL;
}

Session * SessionManager::createNewSession(const std::string & hash)
{
	return SessionManager::getInstance()->sessions[hash];
}

SessionManager *SessionManager::instance = NULL;

