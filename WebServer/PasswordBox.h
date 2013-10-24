#pragma once
#include "Form.h"
#include "BasicInput.h"

namespace html
{
    class Form::PasswordBox: public html::Form::ABasicInput<std::string>
    {
    public:
        PasswordBox(const std::string &name, const std::string &defaultValue = "change the password");
        PasswordBox(const PasswordBox &other);
        virtual ~PasswordBox();

        virtual PasswordBox *clone() const;

    private:
        PasswordBox();
    };
}
