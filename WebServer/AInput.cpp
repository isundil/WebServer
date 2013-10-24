#include "AInput.h"

html::Form::AInput::AInput(const std::string &type)
{
    AHtmlNode::name = "input";
    canHaveChildren = false;
    canHaveStyle = false;
    attributeAdd("type", type);
}

html::Form::AInput::AInput(const std::string &type, const std::string &name) : AInput(type)
{
    attributeAdd("name", name);
}

html::Form::AInput::~AInput()
{ }

const std::string html::Form::AInput::inputName() const
{
    return attributeGet("name");
}

const std::string html::Form::AInput::inputName(const std::string &name)
{
    attributeAdd("name", name);
    return name;
}
