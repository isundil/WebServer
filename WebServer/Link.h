#pragma once
#include "AHtmlNode.h"

namespace html
{
    class Link : public AHtmlNode
    {
    public:
        Link(const std::string &dst, bool local = false);
        Link(const std::string &dst, AHtmlNode *child, bool local = false);
        Link(const std::string &dst, const std::string &child, bool local = false);
        virtual ~Link();

        bool linkDstIsLocal() const;
        std::string linkDstGet() const;
        Link &linkDstSet(const std::string & link);
        Link &linkLocalDstSet(const std::string & link);
    };
}
