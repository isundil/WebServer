#include "Meta.h"
#include "Cookie.h"

using namespace html;

Meta::Meta()
{
}

Meta::~Meta()
{
}

Meta & Meta::setContentType(Meta::contentType type)
{
    std::string value = this->contentTypeToString(type);
    setValue("Content-Type", value);
    return *this;
}

Meta & Meta::setLanguage(const std::string & lg)
{
    setValue("Content-Language", lg, 5);
    return *this;
}

Meta & Meta::setDescription(const std::string &desc)
{
    setValue("Description", desc, 200);
    return *this;
}

Meta & Meta::setKeywords(const std::string & keywords)
{
    setValue("Keywords", keywords, 1000);
    return *this;
}

Meta & Meta::setSubject(const std::string & subj)
{
    setValue("Subject", subj, 75);
    return *this;
}

Meta & Meta::setCopyright(const std::string & value)
{
    setValue("Copyright", value, 125);
    return *this;
}

Meta & Meta::setAuthor(const std::string & value)
{
    setValue("Author", value, 75);
    return *this;
}

Meta & Meta::setAuthorMail(const std::string & value)
{
    setValue("Reply-To", value, 75);
    return *this;
}

Meta & Meta::setPublisher(const std::string & value)
{
    setValue("Publisher", value, 75);
    return *this;
}

Meta & Meta::setIdentifier(const std::string & value)
{
    setValue("Identifier-Url", value);
    return *this;
}

Meta & Meta::setRobotBehaviour(enum Meta::robotIndex _value)
{
    std::string value = "none";

    switch (_value)
    {
    case robotIndex::robot_all:
        value = "all"; break;
    case robotIndex::robot_index:
        value = "Index"; break;
    case robotIndex::robot_noIndex:
        value = "noindex"; break;
    case robotIndex::robot_follow:
        value = "follow"; break;
    case robotIndex::robot_noFollow:
        value = "nofollow"; break;
    default:
        value = "none"; break;
    }
    setValue("Robots", value);
    return *this;
}

Meta & Meta::setRating(enum Meta::rating _value)
{
    std::string value = "general";

    switch (_value)
    {
    case rating::rating_restricted:
        value = "restricted"; break;
    case rating::rating_plus14:
        value = "14 years"; break;
    case rating::rating_plus18:
        value = "mature"; break;
    default:
        value = "general"; break;
    }
    setValue("Rating", value);
    return *this;
}

void Meta::getString(int _indent, bool eol, std::stringstream & out)
{
    const std::string indent = getIndent(_indent);

    for (auto i = values.cbegin(); i != values.cend(); i++)
    {
        out << indent << "<meta name=\"" << (*i).first << "\" content=\"" << (*i).second << "\">";
        if (eol)
            out << std::endl;
    }
}

std::string Meta::getIndent(int lvl)
{
    std::string result;

    for (int i = 0; i < lvl; i++)
        result += " ";
    return result;
}

void Meta::setValue(const std::string & name, const std::string & value)
{
    if (value.find("\"") != value.npos)
        throw InvalidNameException("Forbidden characters in value");
    this->values[name] = value;
}

void Meta::setValue(const std::string & name, const std::string & value, size_t maxLen)
{
    if (value.length() > maxLen)
        throw InvalidNameException("Value is too long");
    return this->setValue(name, value);
}

std::string Meta::contentTypeToString(Meta::contentType type) const
{
    switch (type)
    {
    case contentType::BIG5:
        return "BIG5";
    case contentType::BIG5HKSCS:
        return "BIG5-HKSCS";
    case contentType::CP1252:
        return "cp1252";
    case contentType::EUCJP:
        return "EUCJP";
    case contentType::GB2312:
        return "GB2312";
    case contentType::ISO88591:
        return "ISO-8859-1";
    case contentType::ISO885915:
        return "ISO-8859-15";
    case contentType::SHIFT_JIS:
        return "Shift_JIS";
    case contentType::UTF8:
        return "UTF-8";
    }
    return "";
}
