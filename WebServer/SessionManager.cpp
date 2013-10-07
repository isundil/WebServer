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
