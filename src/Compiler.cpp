#include "Compiler.hpp"
#include <iostream>
#include <regex>
#include "support.hpp"
#include "CodeLine.hpp"
#include "Literal.hpp"

using namespace support;

Compiler::Compiler(const std::vector<std::string> sourceFiles)
{
    m_originalCode = join("\n", sourceFiles);
}

std::ostream &err(void)
{
    std::cerr << "COMPILE ERROR: ";
    return std::cerr;
}

std::string addLiteral(std::map<std::string, Literal> &literals, const Literal value)
{
    std::string strType;

    switch (value.type())
    {
    case LiteralType::String:
        strType = "STRING";
        break;

    case LiteralType::Number:
        strType = "NUMBER";
        break;

    default:
        strType = "UNKNOWN";
        break;
    }

    // Generate a placeholder name for the literal value
    std::string name = "__LITERAL__" + strType + "__" + std::to_string(literals.size()) + "__";

    // Add the literal to the map
    literals[name] = value;

    return name;
}

void regexReplace(std::string &str, const std::string regex, const std::string replacement)
{
    str = std::regex_replace(str, std::regex(regex), replacement);
}

std::string getLine(const std::string str, int &start)
{
    // Find the end of the line
    int end = start;
    while (end < str.size() && str[end] != '\n')
    {
        end++;
    }

    // Extract the line
    std::string line = str.substr(start, end - start);

    // Set the start index to wherever the next line should start
    start = end + 1;

    return line;
}

std::string replaceAt(const std::string str, const int start, const int length, const std::string replacement)
{
    std::string prefix = str.substr(0, start);
    std::string suffix = str.substr(start + length);

    return prefix + replacement + suffix;
}

std::string Compiler::compile(void) const
{
    // std::map<std::string, Literal> literals;
    // std::string inCode = m_originalCode;

    // // Remove carriage returns
    // replaceAllInPlace(inCode, "\r\n", "\n");

    // // Remove escaped newlines
    // replaceAllInPlace(inCode, "\\\n", "");

    // // Replace string literals
    // {
    //     int start;
    //     while ((start = findUnescaped(inCode, '"')) >= 0)
    //     {
    //         int end = findUnescaped(inCode, '"', start + 1);

    //         if (end < 0)
    //         {
    //             err() << "Unterminated string literal" << std::endl;
    //             return std::string();
    //         }

    //         std::string value = inCode.substr(start, end - start + 1);
    //         std::string name = addLiteral(literals, Literal(value, LiteralType::String));
    //         replaceAllInPlace(inCode, value, name);
    //     }
    // }

    // // Replace numeric literals
    // // Note 1: The RegEx does not match the '-' character in front of negative numbers
    // // to avoid accidentally matching the subtraction operator
    // // Note 2: "\x" is not used to match hexadecimal digits because the GCC std::regex does not support it
    // int offset = 0;
    // for (RegexMatch m : getAllMatches("\\b(?:\\d+(?:\\.\\d+)?f?|0x[0-9a-fA-F]+|0b[01]+)\\b", inCode))
    // {
    //     std::string name = addLiteral(literals, Literal(m.str(), LiteralType::Number));
    //     // replaceAllInPlace(inCode, m.str(), name);
    //     inCode = replaceAt(inCode, m.position() + offset, m.length(), name);
    //     offset = name.size() - m.length();
    // }

    // // Generate output code
    // std::string outCode;
    // {
    //     // Iterate through the lines
    //     int idx = 0;
    //     while (idx < inCode.size())
    //     {
    //         // Get the next line
    //         std::string line = getLine(inCode, idx);

    //         // Trim both leading and trailing whitespace and get the indentation level
    //         int indentation = 0;
    //         line = trimWhitespace(line, indentation);

    //         // Ignore empty lines
    //         if (line.empty())
    //         {
    //             continue;
    //         }

    //         // Append the line to the output code
    //         outCode += line;
    //         outCode += '\n';
    //     }
    // }

    // // Put literal values back
    // for (std::pair<std::string, Literal> lit : literals)
    // {
    //     replaceAllInPlace(outCode, lit.first, lit.second.value());
    // }

    // return outCode;

    return m_originalCode;
}
