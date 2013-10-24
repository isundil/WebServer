#include "TextBox.h"

html::Form::TextBox::TextBox(const std::string &name, const std::string &defaultvalue) : ABasicInput<std::string>("text", name, defaultvalue)
{ }

html::Form::TextBox::TextBox(const html::Form::TextBox &other) : TextBox(other.inputName(), other.value())
{ }

html::Form::TextBox::~TextBox()
{ }

html::Form::TextBox *html::Form::TextBox::clone() const
{
    return new TextBox(*this);
}
