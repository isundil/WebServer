#include <sstream>
#include "HttpClient.h"
#include "HashGenerator.h"


const char * HashGenerator::generateHash(const HttpClient &client)
{
	return HashGenerator::doGenerateHash(time(NULL), 0);
}

const char * HashGenerator::doGenerateHash(const time_t timestamp, const short port)
{
	std::stringstream ss;
	ss << timestamp << ":" << port << ":" << rand() % 1000;
	const char * input = ss.str().c_str();
	return input;
}
