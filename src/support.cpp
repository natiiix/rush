#include <iostream>
#include <fstream>
#include "support.hpp"

namespace support
{
void printLn(const char *const str)
{
    std::cout << str << std::endl;
}

void printLn(const std::string str)
{
    printLn(str.c_str());
}

void printLnErr(const char *const str)
{
    std::cerr << "ERROR: " << str << std::endl;
}

void printLnErr(const std::string str)
{
    printLnErr(str.c_str());
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

std::vector<RegexMatch> getAllMatches(const std::string reg, const std::string str)
{
    return getAllMatches(std::regex(reg), str);
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

// Source: https://stackoverflow.com/a/2602258/3043260
std::string readFile(const char *const path)
{
    std::ifstream reader(path);

    if (!reader.is_open())
    {
        return std::string();
    }

    reader.seekg(0, std::ios::end);

    size_t size = reader.tellg();
    std::string buffer(size, ' ');

    reader.seekg(0);

    reader.read(&buffer[0], size);
    reader.close();

    return buffer;
}
}
