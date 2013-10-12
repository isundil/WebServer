#pragma once
#include <string>

class ARootElement;

class Response
{
public:
    Response();
    ~Response();

    Response & setElement(ARootElement &);
    Response & setElement(ARootElement *);
    unsigned int length();
    std::string getValue();

private:
    ARootElement * root;
};
