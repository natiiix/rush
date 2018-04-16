#include <iostream>
#include "support.hpp"

namespace support
{
void printLn(const char *const str)
{
    std::cout << str << std::endl;
}

void printLn(const std::string str)
{
    std::cout << str << std::endl;
}

std::vector<RegexMatch> getAllMatches(const std::regex reg, const std::string str)
{
    std::vector<RegexMatch> matches;

    const std::sregex_iterator end;
    for (std::sregex_iterator iter(str.begin(), str.end(), reg); iter != end; ++iter)
    {
        matches.push_back(RegexMatch(*iter));
    }

    return matches;
}

bool isWhitespace(const char c)
{
    return c == ' ' || c == '\t';
}

std::string trimWhitespace(const std::string input, int &leadingSpaces)
{
    int leading = 0;
    int trailing = 0;

    for (int i = 0; i < input.size() && isWhitespace(input[i]); i++)
    {
        leading++;
    }

    if (leading < input.size())
    {
        for (int i = input.size() - 1; i >= 0 && isWhitespace(input[i]); i++)
        {
            trailing++;
        }
    }

    leadingSpaces = leading;
    return input.substr(leading, input.size() - leading - trailing);
}
}
