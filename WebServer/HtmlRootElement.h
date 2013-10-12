#pragma once

#include "ARootElement.h"

namespace html
{
    class HtmlRootElement: public ARootElement
    {
    public:
        virtual const std::string getValue() const;
        virtual unsigned int length() const;
    };
}