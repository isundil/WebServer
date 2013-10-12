#include "Response.h"
#include "ARootElement.h"

Response::Response()
{
    root = NULL;
}

Response::~Response()
{
    if (root)
        delete root;
}

Response & Response::setElement(ARootElement * value)
{
    if (root)
        delete root;
    root = value;
    return *this;
}

unsigned int Response::length()
{
    if (!root)
        return 0;
    return root->length();
}

std::string Response::getValue()
{
    if (!root)
        return "";
    std::string result = root->getValue();
    return root->getValue();
}
