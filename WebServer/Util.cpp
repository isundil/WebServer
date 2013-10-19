
#include <list>
#include <string>
#include "Util.h"

std::list<std::string> string_split(const std::string &_in, const char separator)
{
    std::list<std::string> result;
    std::string in = _in;
    size_t separatorIndex;

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

void replace_all(std::string &in, const std::string &a, const std::string &b)
{
    size_t pos = 0;
    size_t len = b.length();
    while ((pos = in.find(a, pos +len)) != in.npos)
    {
        in.replace(pos, a.length(), b);
    }
}

static const std::string getAsciiChar(const char * in)
{
    char a, b;
    char result[2];

    // Going uppercase
    a = (in[0] >= 'a' && in[0] <= 'f') ? in[0] -'a' +'A' : in[0];
    b = (in[1] >= 'a' && in[1] <= 'f') ? in[1] - 'a' + 'A' : in[1];

    // Going to number
    a = (a >= 'A' && a <= 'F') ? a - 'A' + 10 : a - '0';
    b = (b >= 'A' && b <= 'F') ? b - 'A' + 10 : b - '0';

    result[0] = (a * 16) + b;
    result[1] = '\0';
    return std::string(result);
}

std::string url_decode(const std::string &in)
{
    std::string result = in;
    unsigned int off = 0;

    while ((off = result.find("+", off)) != result.npos)
        result.replace(off, 1, " ");
    off = 0;
    while ((off = result.find("%", off)) != result.npos)
    {
        result.replace(off, 3, getAsciiChar(&result.c_str()[off + 1]));
        off++;
    }
    return result;
}
