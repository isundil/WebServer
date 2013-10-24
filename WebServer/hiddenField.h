#pragma once
#include "Form.h"
#include "AInput.h"

namespace html
{
    class Form::HiddenField: public Form::AInput
    {
    public:
        HiddenField();
        HiddenField(const std::string &name, const std::string &value);
        ~HiddenField();

        virtual HiddenField *clone() const;
        virtual void setString(const std::string &value);
        virtual const std::string stringValue() const;

    public:
        std::string value() const;
        std::string value(const std::string &value);
    };
}
