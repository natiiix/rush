#include <iostream>
#include <fstream>
#include <sstream>
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

std::string trimWhitespace(const std::string input, int &indentation)
{
    int leading = 0;
    int trailing = 0;

    // Count leading whitespace
    for (int i = 0; i < input.size() && isWhitespace(input[i]); i++)
    {
        leading++;
    }

    indentation = leading;

    // The whole string contains nothing but whitespace
    if (leading == input.size())
    {
        return std::string();
    }

    // Count trailing whitespace
    for (int i = input.size() - 1; i >= 0 && isWhitespace(input[i]); i--)
    {
        trailing++;
    }

    // Return the input string stripped of whitepsace
    return input.substr(leading, input.size() - leading - trailing);
}

// Source: https://stackoverflow.com/a/2602258/3043260
std::string readFile(const char *const path)
{
    // File must be open in binary mode for tellg() to work
    std::ifstream reader(path, std::ifstream::binary);

    // Check if the stream is open
    if (!reader)
    {
        return std::string();
    }

    // Go to end
    reader.seekg(0, std::ios::end);

    // Get the distance from the beginning of the file
    size_t size = reader.tellg();

    // Go to beginning
    reader.seekg(0, std::ios::beg);

    // Create a string and copy the file contents into it
    std::string buffer(size, '\0');
    reader.read(&buffer[0], size);

    // Close the stream (optional)
    reader.close();

    return buffer;
}

// Source: https://stackoverflow.com/a/24315631/3043260
void replaceAllInPlace(std::string &str, const std::string &from, const std::string &to)
{
    // Cannot replace an empty string
    if (from.empty())
    {
        return;
    }

    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos)
    {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}

std::string replaceAll(const std::string &str, const std::string &from, const std::string &to)
{
    std::string newStr = str;
    replaceAllInPlace(newStr, from, to);
    return newStr;
}

// Source: https://stackoverflow.com/a/14267455/3043260
std::vector<std::string> split(const std::string str, const std::string delimiter)
{
    std::vector<std::string> tokens;

    size_t start = 0;
    size_t end = str.find(delimiter);
    while (end != std::string::npos)
    {
        tokens.push_back(str.substr(start, end - start));

        start = end + delimiter.length();
        end = str.find(delimiter, start);
    }

    tokens.push_back(str.substr(start, end));

    return tokens;
}

// Source: https://stackoverflow.com/a/1430774/3043260
std::string join(const std::string separator, const std::vector<std::string> values, const bool trailingSeparator)
{
    std::stringstream ss;

    for (size_t i = 0; i < values.size(); i++)
    {
        ss << values[i];

        if (trailingSeparator || i + 1 < values.size())
        {
            ss << separator;
        }
    }

    return ss.str();
}

int findUnescaped(const std::string str, const char value, const int start)
{
    bool escaped = false;

    for (int i = start; i < str.size(); i++)
    {
        char c = str[i];

        if (escaped)
        {
            escaped = false;
        }
        else if (c == value)
        {
            return i;
        }
        else if (c == '\\')
        {
            escaped = true;
        }
    }

    return -1;
}
}
