#include <sstream>
#include "HttpClient.h"
#include "HashGenerator.h"

const std::string HashGenerator::generateHash(const HttpClient &client)
{
    char * hash = new char[256];
    doGenerateHash(time(NULL), client.getConstSocket()->getPort(), hash);
    std::string result = std::string(hash);
    delete [] hash;
	return result;
}

void HashGenerator::doGenerateHash(const time_t timestamp, const short port, char result[256])
{
	std::stringstream ss;
    int rd = rand() % 1000;
	ss << timestamp << ":" << port << ":" << rd;
    strncpy(result, ss.str().c_str(), 256);
}
