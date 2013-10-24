#pragma once
#include "AInput.h"

namespace html
{
    template <typename T>
    class Form::ABasicInput: public Form::AInput
    {
    public:
        /*!
        * Create a new object called NAME, with value VALUE
        * and of type T
        * example: <input type="text" name="username" value="isundil" />
        * => ABasicInput("text", "username", "isundil")
        */
        ABasicInput(const std::string &type, const std::string &name, const T &defaultValue)
            : AInput(type, name), _type(type)
        {
            value(defaultValue);
        }
        /*!
        * copy constructor
        */
        ABasicInput(const ABasicInput<T> &other)
            : ABasicInput(other.type, other.inputName(), other.value()), _value(other._value)
        { }
        /*!
        * destructor
        */
        virtual ~ABasicInput()
        { }

        /*!
        * Set the value as a string
        */
        virtual void setString(const std::string &value);
        /*!
        * Get the value as a string
        */
        virtual const std::string stringValue() const;

        /*!
        * get the value
        */
        virtual T value() const
        {
            return _value;
        }
        /*!
        * Set the value
        */
        virtual T value(const T &newValue)
        {
            _value = newValue;
            attributeAdd("value", this->stringValue());
            return _value;
        }

    private:
        ABasicInput<T>();

    protected:
        /*!
        * the storage of value
        */
        T _value;
        std::string _type;
    };
}
