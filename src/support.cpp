#include <iostream>
#include <fstream>
#include <sstream>
#include "support.hpp"

namespace support
{
void printLn(const std::string str)
{
    std::cout << str << std::endl;
}

void printLnErr(const std::string str)
{
    std::cerr << "!!! ERROR: " << str << std::endl;
}

void log(const std::string str)
{
    std::cout << str << " ..." << std::endl;
}

void ok(void)
{
    printLn("+++ OK");
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

RegexMatch regexMatch(const std::string str, const std::string regex)
{
    std::smatch match;
    bool success = std::regex_match(str, match, std::regex(regex));

    return RegexMatch(match);
}

RegexMatch regexSearch(const std::string str, const std::string regex)
{
    std::smatch match;
    bool success = std::regex_search(str, match, std::regex(regex));

    return RegexMatch(match);
}

void regexReplace(std::string &str, const std::string regex, const std::string replacement)
{
    str = std::regex_replace(str, std::regex(regex), replacement);
}

bool isWhitespace(const char c)
{
    return c == ' ' || c == '\t';
}

std::string trimWhitespace(const std::string input)
{
    int leading = 0;
    int trailing = 0;

    // Count leading whitespace
    for (int i = 0; i < input.size() && isWhitespace(input[i]); i++)
    {
        leading++;
    }

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

int getIndentation(const std::string str)
{
    for (int i = 0; i < str.size(); i++)
    {
        if (!isWhitespace(str[i]))
        {
            return i;
        }
    }

    return str.size();
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

void replaceAllInPlace(std::string &str, const char from, const char to)
{
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] == from)
        {
            str[i] = to;
        }
    }
}

std::string replaceAll(const std::string &str, const std::string &from, const std::string &to)
{
    std::string newStr = str;
    replaceAllInPlace(newStr, from, to);
    return newStr;
}

std::string replaceAll(const std::string &str, const char from, const char to)
{
    std::string newStr;

    for (int i = 0; i < newStr.size(); i++)
    {
        if (newStr[i] == from)
        {
            newStr[i] = to;
        }
    }

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

bool startsWith(const std::string str, const std::string value)
{
    if (str.size() < value.size())
    {
        return false;
    }

    for (int i = 0; i < value.size(); i++)
    {
        if (str[i] != value[i])
        {
            return false;
        }
    }

    return true;
}

int indexOfFirst(const std::string str, const std::string value)
{
    if (value.size() < str.size())
    {
        return -1;
    }

    for (int i = 0; i < str.size() - value.size() + 1; i++)
    {
        bool equals = true;

        for (int j = 0; j < value.size(); j++)
        {
            if (str[i + j] != value[j])
            {
                equals = false;
                break;
            }
        }

        if (equals)
        {
            return i;
        }
    }

    return -1;
}

bool contains(const std::string str, const std::string value)
{
    return indexOfFirst(str, value) >= 0;
}

std::string getPathRelativeTo(const std::string relativeTo, const std::string path)
{
    // Return the path if either of the paths is empty or if the path is absolute
    if (!relativeTo.size() || !path.size() || path.front() == '/')
    {
        return path;
    }

    std::string newPath = relativeTo;

    replaceAllInPlace(newPath, '\\', '/');

    // Remove the file name from the path we append to
    while (newPath.size() && newPath.back() != '/')
    {
        newPath.pop_back();
    }

    // newPath += replaceAll(path, '\\', '/');
    newPath += path;

    // Remove "this directory" pointers
    regexReplace(newPath, "(^|/)\\./", "$1");
    // Remove unnecessary "parent directory" pointers
    regexReplace(newPath, "[^/]+/\\.\\./", "/");
    // Remove duplicit slashes
    regexReplace(newPath, "/{2,}", "/");

    return newPath;
}
}
