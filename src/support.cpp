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

void printLnWarn(const std::string str)
{
    std::cerr << "*** WARNING: " << str << std::endl;
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

void _addSpace(std::string &str, bool &addSpace)
{
    if (addSpace)
    {
        // Never add spaces to the beginning of a line
        if (str.size())
        {
            str += ' ';
        }

        addSpace = false;
    }
}

std::string getCleanCode(const std::string line)
{
    std::string cleanCode;

    bool inChar = false;
    bool inString = false;
    bool addSpace = false;

    for (int i = 0; i < line.size(); i++)
    {
        char c = line[i];

        // String literal beginning / end
        if (!inChar && c == '"' && !isEscaped(line, i))
        {
            _addSpace(cleanCode, addSpace);
            inString = !inString;
            cleanCode += '"';
        }
        // Character literal beginning / end
        else if (!inString && c == '\'' && !isEscaped(line, i))
        {
            _addSpace(cleanCode, addSpace);
            inChar = !inChar;
            cleanCode += '\'';
        }
        // Characters inside a string or character literal
        else if (inString || inChar)
        {
            cleanCode += c;
        }
        // Beginning of a comment
        else if (c == '/' && line.size() > i + 1 && line[i + 1] == '/')
        {
            break;
        }
        // Whitespace outside of a string literal
        else if (isWhitespace(c))
        {
            addSpace = true;
        }
        else
        {
            _addSpace(cleanCode, addSpace);
            cleanCode += c;
        }
    }

    // Multi-line string literals are illegal
    if (inString)
    {
        throw std::runtime_error("Unexpected end of line (missing string termination)");
    }

    return cleanCode;
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

bool isEscaped(const std::string str, const int index)
{
    bool escaped = false;

    for (int i = index - 1; index >= 0; i--)
    {
        if (str[i] == '\\')
        {
            escaped = !escaped;
        }
        else
        {
            break;
        }
    }

    return escaped;
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

std::string normalizePath(const std::string path)
{
    std::string newPath = path;

    // Convert Windows path separators to UNIX ones
    replaceAllInPlace(newPath, '\\', '/');

    // Remove duplicit slashes
    regexReplace(newPath, "/{2,}", "/");
    // Remove "this directory" pointers
    regexReplace(newPath, "(^|/)\\./", "$1");
    // Remove unnecessary "parent directory" pointers
    regexReplace(newPath, "[^/]+/\\.\\./", "/");

    return newPath;
}

std::string getPathRelativeTo(const std::string relativeTo, const std::string path)
{
    // Return the path if either of the paths is empty or if the path is absolute
    if (!relativeTo.size() || !path.size() || path.front() == '/')
    {
        return path;
    }

    std::string newPath = relativeTo;

    // Remove the file name from the path we append to
    while (newPath.size() && newPath.back() != '/' && newPath.back() != '\\')
    {
        newPath.pop_back();
    }

    newPath += path;

    return normalizePath(newPath);
}
}
