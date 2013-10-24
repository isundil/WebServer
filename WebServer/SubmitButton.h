#pragma once
#include "AInput.h"

namespace html
{
    class Form::SubmitButton : public AHtmlNode
    {
    public:
        SubmitButton(const std::string &text = "Send");
        virtual ~SubmitButton();

        std::string name() const;
        std::string name(const std::string &newName);
    };
}
