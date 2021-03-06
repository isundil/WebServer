#include <sstream>
#include <algorithm>
#include <string>
#include "Cookie.h"
#include "HtmlRootElement.h"
#include "Meta.h"

using namespace html;

HtmlRootElement::HtmlRootElement(const std::string & _title) : title(_title)
{
    upToDate = false;
    metaElem = new html::Meta();
}

HtmlRootElement::~HtmlRootElement()
{
    delete metaElem;
}

Meta & HtmlRootElement::getMeta() const
{
    return *(this->metaElem);
}

void HtmlRootElement::updateResult()
{
    if (upToDate)
        return;
    std::stringstream ss;

    ss  << "<!DOCTYPE html>" << std::endl
        << "<html>" << std::endl
        << "  <head>" << std::endl
        << "    <title>" << this->title << "</title>" << std::endl;
    metaElem->getString(4, true, ss);
    for (auto i = scriptList.cbegin(); i != scriptList.cend(); i++)
        ss << "    <script type=\"text/javascript\" src=\"" << *i << "\"></script>" << std::endl;
    for (auto i = cssList.cbegin(); i != cssList.cend(); i++)
        ss << "    <link href=\"" << *i << "\" rel=\"stylesheet\" type=\"text/css\">" << std::endl;
    ss << "  </head>" << std::endl;

    ss << "  <body>" << std::endl << this->toString();
    ss << "  </body>" << std::endl
        << "</html>";

    this->result = ss.str();
    upToDate = true;
}

const std::string HtmlRootElement::getValue()
{
    updateResult();
    return result;
}

unsigned int HtmlRootElement::length()
{
    updateResult();
    return result.length();
}

HtmlRootElement & HtmlRootElement::addScript(const std::string & s)
{
    if (s.find("\"") != s.npos)
        throw InvalidNameException(s);
    scriptList.push_back(s);
    return *this;
}

HtmlRootElement & HtmlRootElement::addStyle(const std::string & s)
{
    if (s.find("\"") != s.npos)
        throw InvalidNameException(s);
    cssList.push_back(s);
    return *this;
}
