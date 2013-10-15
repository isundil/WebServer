#pragma once
#include <list>
#include <string>

/*!
* split a string in multiples string, using separator.
* return a list of these strings
*/
std::list<std::string> string_split(const std::string &_in, const char separator);

/*!
* remove all the leading ' ' (space) in string str.
* DOES NOT modify parameter, return the result
*/
std::string epur_begin_str(const char *str);

/*!
* replace all the strings "before" by "after", in the "input" string.
* modify the "input" parameter
*/
void replace_all(std::string &in, const std::string &before, const std::string & after);
