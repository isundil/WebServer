#pragma once
#include <string>
#include "AHtmlNode.h"

namespace html
{
    class P: public AHtmlNode
    {
    public:
        P(const std::string &content ="");
        virtual ~P();

        virtual const std::string toContentString();

    protected:
        std::string content;
    };
}
