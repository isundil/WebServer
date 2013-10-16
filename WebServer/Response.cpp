#include "Response.h"
#include "ARootElement.h"

Response::Response()
{
    root = NULL;
    setContentType();
}

Response::~Response()
{
    if (root)
        delete root;
}

Response & Response::setContentType(const std::string & value)
{
    this->contentType = value;
    return *this;
}

const std::string Response::getContentType() const
{
    return contentType;
}

Response & Response::setElement(ARootElement * value)
{
    if (root)
        delete root;
    root = value;
    return *this;
}

ARootElement * Response::getElement()
{
    return root;
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
