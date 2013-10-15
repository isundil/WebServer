#pragma once

#include <time.h>

class HttpClient;

/*!
* Create an unique hash that correspond to an client
*/
class HashGenerator
{
public:
    /*!
    * Create an unique hash that correspond to the client, 
    * using his port, time and a randomized number
    */
    static const std::string generateHash(const HttpClient &request);

private:
    /*!
    * Create an unique hash that correspond to the port,
    * the timestamp and a randomized number.
    * Store the result in result[]
    */
    static void doGenerateHash(const time_t timestamp, const short port, char result[256]);
};
