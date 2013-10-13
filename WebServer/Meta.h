#pragma once

#include <sstream>
#include <map>

namespace html
{
    class Meta
    {
    public:
        enum contentType {
            UTF8,
            ISO88591,
            ISO885915,
            CP1252,
            BIG5,
            GB2312,
            BIG5HKSCS,
            SHIFT_JIS,
            EUCJP
        };
        enum robotIndex {
            robot_all,
            robot_index,
            robot_noIndex,
            robot_follow,
            robot_noFollow,
            robot_none
        };
        enum rating {
            rating_all,
            rating_restricted,
            rating_plus14,
            rating_plus18
        };

    public:
        Meta();
        virtual ~Meta();

        Meta & setContentType(enum contentType);
        Meta & setLanguage(const std::string & lg);
        Meta & setDescription(const std::string & description);
        Meta & setKeywords(const std::string & keywords);
        Meta & setSubject(const std::string & subject);
        Meta & setCopyright(const std::string & copyright);
        Meta & setAuthor(const std::string & author);
        Meta & setAuthorMail(const std::string & author);
        Meta & setPublisher(const std::string & publisher);
        Meta & setIdentifier(const std::string & url);
        Meta & setRobotBehaviour(enum robotIndex);
        Meta & setRating(enum rating);

        void getString(int indent, bool eol, std::stringstream & out);

    private:
        std::map<std::string, std::string> values;

    private:
        std::string getIndent(int indentLevel);
        void setValue(const std::string & name, const std::string & value, size_t maxLen);
        void setValue(const std::string & name, const std::string & value);
        std::string contentTypeToString(contentType type) const;
    };
}
