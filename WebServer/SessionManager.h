#pragma once

#include <string>
#include <map>

class Session;

class SessionManager
{
public:
    static SessionManager *getInstance();

private:
    SessionManager();

private:
    std::map<const std::string, Session *> sessions;

private:
    static SessionManager *instance;
};

SessionManager *SessionManager::instance = NULL;
