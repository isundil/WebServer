#include "Paragraph.h"

using namespace html;

P::P(const std::string &v) : content(v)
{
    this->canHaveChildren = true;
    this->canHaveStyle = true;
    this->name = "p";
}

P::~P()
{}

const std::string P::toContentString()
{
    return content;
}
