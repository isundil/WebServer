#pragma once

#include <string>
#include <map>

class Session;

class SessionManager
{
public:
    static SessionManager *getInstance();
	static Session * getSession(const std::string & hash);
	static Session * createNewSession(const std::string & hash);

private:
    SessionManager();

private:
    std::map<const std::string, Session *> sessions;

private:
    static SessionManager *instance;
};

