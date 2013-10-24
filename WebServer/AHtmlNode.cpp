#include "AHtmlNode.h"
#include "Paragraph.h"

using namespace html;

AHtmlNode::AHtmlNode(const std::string & style) : AHtmlNode()
{
    this->styleName = new std::string(style);
}

AHtmlNode::AHtmlNode()
{
    this->styleName = NULL;
    canHaveChildren = true;
    canHaveStyle = true;
    name = "";
}

AHtmlNode::~AHtmlNode()
{
    if (styleName)
        delete styleName;
}

AHtmlNode &AHtmlNode::styleSet(const std::string & style)
{
    if (styleName)
        delete styleName;
    styleName = new std::string(style);
    return *this;
}

AHtmlNode &AHtmlNode::styleRemove()
{
    if (!styleName)
        return *this;
    delete styleName;
    styleName = NULL;
    return *this;
}

std::string * AHtmlNode::styleGet() const
{
    return styleName;
}

AHtmlNode &AHtmlNode::attributeAdd(const std::string &key, const std::string &value)
{
    attributes[key] = value;
    return *this;
}

const std::string AHtmlNode::attributeGet(const std::string &key) const
{
    std::string result;

    try {
        result = attributes.at(key);
    }
    catch (std::out_of_range &e)
    {
        (void) e;
    }
    return result;
}

AHtmlNode &AHtmlNode::attributeRemove(const std::string &key)
{
    attributes.erase(key);
    return *this;
}

AHtmlNode &AHtmlNode::operator<<(const std::string &value)
{
    *this << new html::P(value);
    return (*this);
}

AHtmlNode &AHtmlNode::operator<<(AHtmlNode *next)
{
    children.push_back(next);
    return *this;
}

const std::string AHtmlNode::toBeginString()
{
    std::string result;

    if (name == "")
        return "";
    result = "<" +name;
    for (auto i = attributes.cbegin(); i != attributes.cend(); i++)
        result += " " +(*i).first + "=\"" + (*i).second + "\"";
    if (canHaveStyle && styleName)
        result += " style=\"" + *styleName + "\"";
    if (canHaveChildren)
        return result + ">";
    return result + "/>";
}

const std::string AHtmlNode::toEndString()
{
    if (!canHaveChildren || name == "")
        return "";
    return "</" + name + ">\n";
}

const std::string AHtmlNode::toContentString()
{
    return "";
}

const std::string AHtmlNode::toString()
{
    std::string result;

    result = this->toBeginString();
    result += this->toContentString();
    for (auto i = children.begin(); i != children.end(); i++)
        result += ((*i)->toString());
    result += this->toEndString();
    return result;
}

const std::list<AHtmlNode *> &AHtmlNode::getChildren() const
{
    return children;
}
