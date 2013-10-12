#pragma once
#include <list>
#include <string>

std::list<std::string> string_split(const std::string &_in, const char separator);
std::string epur_begin_str(const char *str);
void replace_all(std::string &, const std::string &before, const std::string & after);
