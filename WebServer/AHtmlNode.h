#pragma once
#include <string>
#include <list>
#include <map>

namespace html
{
    class AHtmlNode
    {
    public:
        AHtmlNode(const std::string &styleName);
        AHtmlNode();
        virtual ~AHtmlNode();

        AHtmlNode &styleSet(const std::string & stylename);
        std::string * styleGet() const;
        AHtmlNode &styleRemove();

        AHtmlNode &attributeAdd(const std::string &key, const std::string &value);
        const std::string attributeGet(const std::string &key) const;
        AHtmlNode &attributeRemove(const std::string &key);

        virtual AHtmlNode & operator<<(const std::string &child);
        virtual AHtmlNode & operator<<(AHtmlNode *child);

        const std::string & toAttributesString();
        virtual const std::string toString();

    protected:
        bool canHaveChildren;
        bool canHaveStyle;

        virtual const std::string toBeginString();
        virtual const std::string toEndString();
        virtual const std::string toContentString();
        
        std::string name;

    private:
        std::string * styleName;
        std::list<AHtmlNode *> children;
        std::map<std::string, std::string> attributes;
    };
}
