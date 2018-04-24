#include "Compiler.hpp"
#include <iostream>
#include <fstream>
#include <map>
#include <exception>
#include "support.hpp"
#include "CodeLine.hpp"
#include "Literal.hpp"

using namespace support;

Compiler::Compiler(const std::string mainSourcePath)
{
    loadFile(mainSourcePath);
}

void Compiler::loadFile(const std::string path)
{
    if (contains(m_loadedFiles, path))
    {
        printLnErr("File already loaded: " + path);
        return;
    }

    printLn("Reading file: \"" + path + "\"");

    m_loadedFiles.push_back(path);
    std::ifstream file(path);

    if (!file)
    {
        throw std::runtime_error("Unable to open file for reading");
    }

    int lineCounter = 1;
    for (std::string line; getline(file, line);)
    {
        RegexMatch match = regexMatch(line, "\\w*#include \"([^\"]+)\"\\w*");

        if (!match.empty())
        {
            loadFile(getPathRelativeTo(path, match[0]));
            continue;
        }

        m_lines.push_back(CodeLine(path, lineCounter, line));
        m_allCode += line + "\n";
        lineCounter++;
    }

    printLn("File loaded: \"" + path + "\"");
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
    std::map<std::string, Literal> literals;
    std::string inCode = m_allCode;

    // Remove carriage returns
    replaceAllInPlace(inCode, "\r\n", "\n");

    // Remove escaped newlines
    replaceAllInPlace(inCode, "\\\n", "");

    // Escape double quotes in character literals
    replaceAllInPlace(inCode, "'\"'", "'\\\"'");

    // Replace string literals
    {
        int start;
        while ((start = findUnescaped(inCode, '"')) >= 0)
        {
            int end = findUnescaped(inCode, '"', start + 1);

            if (end < 0)
            {
                printLnErr("Unterminated string literal");
                return std::string();
            }

            std::string value = inCode.substr(start, end - start + 1);
            std::string name = addLiteral(literals, Literal(value, LiteralType::String));
            replaceAllInPlace(inCode, value, name);
        }
    }

    // Replace numeric literals
    // Note 1: The RegEx does not match the '-' character in front of negative numbers
    // to avoid accidentally matching the subtraction operator
    // Note 2: "\x" is not used to match hexadecimal digits because the GCC std::regex does not support it
    int offset = 0;
    for (RegexMatch m : getAllMatches("\\b(?:\\d+(?:\\.\\d+)?f?|0x[0-9a-fA-F]+|0b[01]+)\\b", inCode))
    {
        std::string name = addLiteral(literals, Literal(m.str(), LiteralType::Number));

        // Replace the literal value by its placeholder
        inCode = replaceAt(inCode, m.position() + offset, m.length(), name);

        // Since the placeholders have different length from the original literal values
        // we must compensate for this difference in the indexing by adding an ofset to all indices
        offset += name.size() - m.length();
    }

    // Generate output code
    std::string outCode;
    {
        // Iterate through the lines
        int idx = 0;
        while (idx < inCode.size())
        {
            // Get the next line
            std::string line = getLine(inCode, idx);

            // Trim both leading and trailing whitespace
            line = getCleanCode(line);

            // Ignore empty lines
            if (line.empty())
            {
                continue;
            }

            // Append the line to the output code
            outCode += line;
            outCode += '\n';
        }
    }

    // Put literal values back
    for (std::pair<std::string, Literal> lit : literals)
    {
        replaceAllInPlace(outCode, lit.first, lit.second.value());
    }

    return outCode;
}
