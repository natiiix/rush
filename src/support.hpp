#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <regex>
#include "RegexMatch.hpp"

namespace support
{
void printLn(const std::string str);
void printLnErr(const std::string str);
void log(const std::string str);
void ok(void);
std::vector<RegexMatch> getAllMatches(const std::regex reg, const std::string str);
std::vector<RegexMatch> getAllMatches(const std::string reg, const std::string str);
RegexMatch regexMatch(const std::string str, const std::string regex);
RegexMatch regexSearch(const std::string str, const std::string regex);
void regexReplace(std::string &str, const std::string regex, const std::string replacement);
bool isWhitespace(const char c);
std::string trimWhitespace(const std::string input);
int getIndentation(const std::string str);
std::string readFile(const char *const path);
void replaceAllInPlace(std::string &str, const std::string &from, const std::string &to);
void replaceAllInPlace(std::string &str, const char from, const char to);
std::string replaceAll(const std::string &str, const std::string &from, const std::string &to);
std::string replaceAll(const std::string &str, const char from, const char to);
std::vector<std::string> split(const std::string str, const std::string delimiter);
std::string join(const std::string separator, const std::vector<std::string> values, const bool trailingSeparator = false);
bool startsWith(const std::string str, const std::string value);
int findUnescaped(const std::string str, const char value, const int start = 0);
int indexOfFirst(const std::string str, const std::string value);
bool contains(const std::string str, const std::string value);
std::string getPathRelativeTo(const std::string relativeTo, const std::string path);

template <class T, class U, class F>
void map(const std::vector<T> src, std::vector<U> &dest, const F f)
{
    dest.resize(src.size());
    std::transform(src.begin(), src.end(), dest.begin(), f);
}

template <class T>
std::vector<T> toVector(const T arr[], const int length)
{
    if (length < 0)
    {
        return nullptr;
    }

    std::vector<T> vec(arr, arr + length);
    return vec;
}

template <class T>
int indexOfFirst(const std::vector<T> vect, const T value)
{
    for (int i = 0; i < vect.size(); i++)
    {
        if (vect[i] == value)
        {
            return i;
        }
    }

    return -1;
}

template <class T>
bool contains(const std::vector<T> vect, const T value)
{
    return indexOfFirst(vect, value) >= 0;
}
}
