#include "Link.h"
#include "Paragraph.h"

using namespace html;

Link::Link(const std::string &dst, bool local)
{
    this->canHaveChildren = true;
    this->canHaveStyle = true;
    this->name = "a";
    if (local)
        linkLocalDstSet(dst);
    else
        linkDstSet(dst);
}

Link::Link(const std::string &dst, AHtmlNode *child, bool local) : Link(dst, local)
{
    (*this) << child;
}

Link::Link(const std::string &dst, const std::string &str, bool local) : Link(dst, new P(str), local)
{}

Link::~Link()
{}

std::string Link::linkDstGet() const
{
    std::string result = attributeGet("href");
    if (result.at(0) == '#')
        return result.substr(1);
    return result;
}

Link &Link::linkDstSet(const std::string & link)
{
    this->attributeAdd("href", link);
    return *this;
}

Link &Link::linkLocalDstSet(const std::string & link)
{
    this->attributeAdd("href", "#" +link);
    return *this;
}

bool Link::linkDstIsLocal() const
{
    return attributeGet("href").at(0) == '#';
}
