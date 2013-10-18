#pragma once

#include "AHtmlNode.h"

namespace html
{
    class Anchor : public AHtmlNode
    {
    public:
        Anchor(const std::string &name = "");

        std::string nameGet() const;
        Anchor &nameSet(const std::string & name);
    };
}
