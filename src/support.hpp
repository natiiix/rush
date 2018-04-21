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
std::string trimWhitespace(const std::string input, int &leadingSpaces);
std::string readFile(const char *const path);

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
