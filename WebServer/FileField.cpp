#include <fstream>
#include "FileField.h"

FileInputData::FileInputData()
{
    ss = nullptr;
}

FileInputData::FileInputData(const std::string &f, std::stringstream * const s, unsigned long _s)
{
    ss = s;
    _filename = f;
    size = _s;
}

FileInputData::~FileInputData()
{ }

void FileInputData::save(const std::string &filename) const
{
    std::ofstream o(filename);
    char buffer[512];

    o.open(filename, std::ios_base::trunc || std::ios_base::out);
    if (!o.is_open())
        throw std::runtime_error("Cannot open file " +filename +" for writting");
    for (unsigned long i = 0; i < size; i += 512)
    {
        ss->read(buffer, i +512 < size ? size-i : 512);
        o.write(buffer, i + 512 < size ? size - i : 512);
    }
    o.close();
}

html::Form::FileField::FileField()
{
    AHtmlNode::name = "input";
    canHaveChildren = false;
    canHaveStyle = true;
    attributeAdd("type", "file");
}

html::Form::FileField::FileField(const std::string &name) : FileField()
{
    attributeAdd("name", name);
}

html::Form::FileField::FileField(const Form::FileField &name) : FileField()
{
    attributeAdd("name", name.attributeGet("name"));
    _data = name._data;
}

html::Form::FileField::~FileField()
{ }

const std::string html::Form::FileField::inputName() const
{
    return attributeGet("name");
}

FileInputData *html::Form::FileField::data() const
{
    return _data;
}

html::Form::FileField *html::Form::FileField::clone() const
{
    return new FileField(*this);
}

FileInputData *html::Form::FileField::data(FileInputData * const d)
{
    _data = d;
    return _data;
}
