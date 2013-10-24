#pragma once
#include "BasicInput.h"

namespace html
{
    class Form::TextBox: public Form::ABasicInput<std::string>
    {
    public:
        TextBox(const std::string &name, const std::string &defaultValue="");
        TextBox(const TextBox &other);
        virtual ~TextBox();

        virtual TextBox *clone() const;

    private:
        TextBox();
    };
}
