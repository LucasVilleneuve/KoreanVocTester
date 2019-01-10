//
// Created by Lucas on 03-Dec-18.
//

#ifndef KOREANVOCTESTER_STRINGOPS_HPP
#define KOREANVOCTESTER_STRINGOPS_HPP

#include <string>
#include <algorithm>

inline std::string& ltrim(std::string& s, const char* t = " \t\n\r\f\v")
{
    s.erase(0, s.find_first_not_of(t));
    return s;
}

inline std::string& rtrim(std::string& s, const char* t = " \t\n\r\f\v")
{
    s.erase(s.find_last_not_of(t) + 1);
    return s;
}

inline std::string& trim(std::string& s, const char* t = " \t\n\r\f\v")
{
    return ltrim(rtrim(s, t), t);
}

inline std::string &removeSpaces(std::string &str)
{
  str.erase(std::remove_if(str.begin(), str.end(),
						   [](unsigned char c){return std::isspace(c);}),
			 str.end());
  return str;
}

inline std::string &toLower(std::string &str)
{
  std::transform(str.begin(), str.end(), str.begin(), ::tolower);
  return str;
}

#endif //KOREANVOCTESTER_STRINGOPS_HPP
