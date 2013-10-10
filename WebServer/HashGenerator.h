#pragma once

#include <time.h>

class HttpClient;

class HashGenerator
{
public:
	static const std::string generateHash(const HttpClient &request);

private:
	static void doGenerateHash(const time_t timestamp, const short port, char result[256]);
};
