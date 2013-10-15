#pragma once

#include <string>
#include <list>
#include "ARootElement.h"

namespace html
{
    class Meta;

    /*!
    * HTML container. contains the <!DOCTYPE>, <html> and all the header stuff.
    * body's content can be added using operator '<<'
    */
    class HtmlRootElement: public ARootElement
    {
    public: //public methods
        /*!
        * Constructor. Set the title of the page to "name"
        */
        HtmlRootElement(const std::string & name = "");
        virtual ~HtmlRootElement();

        /*!
        * Add a script file to be included into the <head> html tag
        */
        HtmlRootElement & addScript(const std::string & src);

        /*!
        * Add a style file to be included into the <head> html tag
        */
        HtmlRootElement & addStyle(const std::string & src);

        /*!
        * Get the meta instruction of the heading
        */
        Meta & getMeta() const;

    public: //public inherited methods
        /*!
        * Get the html code to be sent to the client
        */
        virtual const std::string getValue();

        /*!
        * Get the html code's length to be sent to the client. Used for the http header
        */
        virtual unsigned int length();

    private: //private methods
        /*!
        * update the html code to be sent to the client.
        * This cache permit to avoid losing time from calling length() then getValue()
        */
        void updateResult();

    private: //private attributes

        /*!
        * title of the page
        */
        std::string title;
        /*!
        * is updateResult have to be called (false) ? Or the cache is up-to-date (true)
        */
        bool upToDate;
        /*!
        * html code to be sent to the client
        */
        std::string result;
        /*!
        * list of scripts' path to be included in the <head> section
        */
        std::list<std::string> scriptList;
        /*!
        * list of styles' path to be included in the <head> section
        */
        std::list<std::string> cssList;
        /*!
        * Meta informations, to be used in the <HEAD> section for referencing
        */
        Meta * metaElem;
    };
}
