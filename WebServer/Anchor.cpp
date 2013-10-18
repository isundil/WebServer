#include "Anchor.h"

using namespace html;

Anchor::Anchor(const std::string &n)
{
    this->nameSet(n);
    this->canHaveChildren = false;
    this->canHaveStyle = false;
    this->name = "a";
}

Anchor &Anchor::nameSet(const std::string &n)
{
    this->attributeAdd("name", n);
    return *this;
}

std::string Anchor::nameGet() const
{
    return this->attributeGet("name");
}
