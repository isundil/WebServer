#include <fstream>
#include "FileField.h"

FileInputData::FileInputData()
{
    ss = nullptr;
}

FileInputData::FileInputData(const std::string &f, std::stringstream * const s, unsigned long _begin, unsigned long _end)
{
    ss = s;
    filename = f;
    begin = _begin;
    end = _end;
}

FileInputData::~FileInputData()
{ }

void FileInputData::save(const std::string &filename) const
{
    //std::ofstream o(filename);
    FILE *o;
    char buffer[512];
    std::streamoff toRead;
    std::streamoff pos;
    const std::streamoff size = end - begin;

    pos = ss->tellg();
    ss->seekg(begin);
    fopen_s(&o, filename.c_str(), "w+b");
    //o.open(filename, std::ios_base::trunc | std::ios_base::out | std::ios_base::binary);
    if (!o)
        throw std::runtime_error("Cannot open file " +filename +" for writting");
    for (unsigned long i = 0; i < size; i += 512)
    {
        toRead = i + 512 > size ? size - i : 512;
        ss->read(buffer, toRead);
        fwrite(buffer, toRead, 1, o);
        //o.write(buffer, toRead);
    }
    fclose(o);
    //o.close();
    ss->seekg(pos);
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
