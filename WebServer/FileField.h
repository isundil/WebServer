#pragma once
#include "Form.h"
#include "AInput.h"

class FileInputData
{
public:
    FileInputData();
    FileInputData(const std::string &filename, std::stringstream * const, unsigned long begin, unsigned long end);
    virtual ~FileInputData();

    virtual void save(const std::string &filename) const;

private:
    std::stringstream *ss;
    std::string filename;
    unsigned long begin;
    unsigned long end;
};

namespace html
{
    class Form::FileField: public AHtmlNode
    {
    public:
        FileField();
        FileField(const FileField &);
        FileField(const std::string &name);

        ~FileField();

        virtual const std::string inputName() const;

        virtual Form::FileField *clone() const;

        virtual FileInputData *data(FileInputData * const data);
        virtual FileInputData *data() const;

    private:
        std::string name;
        FileInputData *_data;
    };
}
