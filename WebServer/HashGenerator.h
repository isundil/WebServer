#pragma once

#include <time.h>

class HttpClient;

class HashGenerator
{
public:
	static const char * generateHash(const HttpClient &request);

private:
	static const char * doGenerateHash(const time_t timestamp, const short port);
};
