
#include <list>
#include <string>
#include "Util.h"

std::list<const std::string> string_split(const std::string &_in, const char separator)
{
    std::list<const std::string> result;
    std::string in = _in;
    int separatorIndex;

    do
    {
        separatorIndex = in.find(separator);
        result.push_back(in.substr(0, separatorIndex));
        in = in.substr(separatorIndex + 1);
    } while (separatorIndex != in.npos);

    return result;
}

std::string epur_begin_str(const char *str)
{
    while (*str == ' ')
        str++;
    return std::string(str);
}
