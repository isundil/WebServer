#include "PasswordBox.h"

html::Form::PasswordBox::PasswordBox(const std::string &name, const std::string &defaultvalue) : ABasicInput<std::string>("password", name, defaultvalue)
{ }

html::Form::PasswordBox::PasswordBox(const html::Form::PasswordBox &other) : PasswordBox(other.inputName(), other.value())
{ }

html::Form::PasswordBox::~PasswordBox()
{ }

html::Form::PasswordBox *html::Form::PasswordBox::clone() const
{
    return new PasswordBox(*this);
}
