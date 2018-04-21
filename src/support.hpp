#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <regex>
#include "RegexMatch.hpp"

namespace support
{
void printLn(const char *const str);
void printLn(const std::string str);
void printLnErr(const char *const str);
void printLnErr(const std::string str);
std::vector<RegexMatch> getAllMatches(const std::regex reg, const std::string str);
std::vector<RegexMatch> getAllMatches(const std::string reg, const std::string str);
bool isWhitespace(const char c);
std::string trimWhitespace(const std::string input, int &indentation);
std::string readFile(const char *const path);
void replaceAllInPlace(std::string &str, const std::string &from, const std::string &to);
std::string replaceAll(const std::string &str, const std::string &from, const std::string &to);
std::vector<std::string> split(const std::string str, const std::string delimiter);
std::string join(const std::string delimiter, const std::vector<std::string> values);

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
}
