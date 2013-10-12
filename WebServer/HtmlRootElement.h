#pragma once

#include <string>
#include <list>
#include "ARootElement.h"

namespace html
{
    class HtmlRootElement: public ARootElement
    {
    public: //public methods
        HtmlRootElement(const std::string & name = "");
        virtual ~HtmlRootElement();

        HtmlRootElement & addScript(const std::string & src);
        HtmlRootElement & addStyle(const std::string & src);

    public: //public inherited methods
        virtual const std::string getValue();
        virtual unsigned int length();

    private: //private methods
        void updateResult();

    private: //private attributes
        std::string title;
        bool upToDate;
        std::string result;
        std::list<std::string> scriptList;
        std::list<std::string> cssList;
    };
}
