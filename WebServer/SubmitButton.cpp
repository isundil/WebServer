#include "SubmitButton.h"

using namespace html;

Form::SubmitButton::SubmitButton(const std::string &name)
{
    attributeAdd("type", "submit");
    attributeAdd("value", name);
    AHtmlNode::name = "input";
    this->canHaveChildren = false;
    this->canHaveStyle = true;
}

Form::SubmitButton::~SubmitButton()
{ }

std::string Form::SubmitButton::name() const
{
    return attributeGet("value");
}

std::string Form::SubmitButton::name(const std::string &newName)
{
    attributeAdd("value", newName);
    return newName;
}
