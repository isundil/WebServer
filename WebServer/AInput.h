#pragma once
#include "Form.h"

namespace html
{
    class Form::AInput: public AHtmlNode
    {
    public:
        AInput(const std::string &type);
        AInput(const std::string &type, const std::string &name);
        virtual ~AInput();

        virtual AInput *clone() const = 0;
        virtual void setString(const std::string &value) =0;
        virtual const std::string stringValue() const =0;

        const std::string inputName(const std::string &name);
        const std::string inputName() const;
    };
}
