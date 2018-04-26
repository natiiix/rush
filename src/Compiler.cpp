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

// To be potentially used in the future to tell the user the origin of an error
// std::string getLineIdentifier(const std::string sourcePath, const int lineNumber)
// {
//     return " (" + sourcePath + " : " + std::to_string(lineNumber) + ")";
// }

void Compiler::loadFile(const std::string path)
{
    if (contains(m_loadedFiles, path))
    {
        printLnWarn("File already loaded: " + path);
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
    for (std::string line; getline(file, line); lineCounter++)
    {
        processLine(line, path, lineCounter);
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

std::string replaceAt(const std::string str, const int start, const int length, const std::string replacement)
{
    std::string prefix = str.substr(0, start);
    std::string suffix = str.substr(start + length);

    return prefix + replacement + suffix;
}

std::string Compiler::compile(void) const
{
    std::string code;

    // Include headers
    for (std::string include : m_includes)
    {
        code += "#include <" + include + ">\n";
    }

    // Iterate through code lines
    std::vector<int> indentationLevels;
    indentationLevels.push_back(0);

    for (CodeLine codeLine : m_lines)
    {
        // Get the code of this line
        std::string line = codeLine.code;

        // Higher indentation level
        if (codeLine.indentation > indentationLevels.back())
        {
            code += "{\n";
            indentationLevels.push_back(codeLine.indentation);
        }
        // Lower indentation level
        else if (codeLine.indentation < indentationLevels.back())
        {
            code += "}\n";
            indentationLevels.pop_back();
        }

        // // Create a vector to temporarily store literal values
        // std::map<std::string, Literal> literals;

        // // Escape double quotes in character literals
        // // replaceAllInPlace(line, "'\"'", "'\\\"'");

        // // Replace string literals
        // for (char c : {'\'', '`', '"'})
        // {
        //     int start;
        //     while ((start = findUnescaped(line, c)) >= 0)
        //     {
        //         int end = findUnescaped(line, c, start + 1);

        //         // This should never really even happen at this point
        //         if (end < 0)
        //         {
        //             printLnErr("Unterminated string literal");
        //             return std::string();
        //         }

        //         std::string value = line.substr(start, end - start + 1);
        //         std::string name = addLiteral(literals, Literal(value, LiteralType::String));
        //         replaceAllInPlace(line, value, name);
        //     }
        // }

        // // Replace numeric literals
        // // Note 1: The RegEx does not match the '-' character in front of negative numbers
        // // to avoid accidentally matching the subtraction operator
        // // Note 2: "\x" is not used to match hexadecimal digits because the GCC std::regex does not support it
        // int offset = 0;
        // for (RegexMatch m : getAllMatches("\\b(?:\\d+(?:\\.\\d+)?f?|0x[0-9a-fA-F]+|0b[01]+)\\b", line))
        // {
        //     std::string name = addLiteral(literals, Literal(m.str(), LiteralType::Number));

        //     // Replace the literal value by its placeholder
        //     line = replaceAt(line, m.position() + offset, m.length(), name);

        //     // Since the placeholders have different length from the original literal values
        //     // we must compensate for this difference in the indexing by adding an ofset to all indices
        //     offset += name.size() - m.length();
        // }

        // TODO: Further line processing

        // Put literal values back
        for (std::pair<std::string, Literal> lit : m_literals)
        {
            replaceAllInPlace(line, lit.first, lit.second.value());
        }

        // If a line ends with a backslash, the next line is supposed to be appended to it
        if (line.back() == '\\')
        {
            line.pop_back();
        }
        // Regular lines have a newline character at the end
        else
        {
            line += '\n';
        }

        // Append the line to the code
        code += line;
    }

    // Terminate all the remaining scopes
    while (indentationLevels.size() > 1)
    {
        code += "}\n";
        indentationLevels.pop_back();
    }

    return code;
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

void Compiler::processLine(const std::string line, const std::string origin, const int number)
{
    {
        // Include code from another file
        RegexMatch match = regexMatch(line, "\\s*#include\\s+\"([^\"]+)\";?\\s*");
        if (match.success())
        {
            loadFile(getPathRelativeTo(origin, match[0]));
            return;
        }

        // Include C++ header
        match = regexMatch(line, "\\s*#include\\s+\\<?([^\\<\\>;]+)\\>?;?\\s*");
        if (match.success())
        {
            if (contains(m_includes, match[0]))
            {
                printLnWarn("Header already included: " + match[0]);
            }
            else
            {
                m_includes.push_back(match[0]);
            }

            return;
        }
    }

    std::string clean;

    char inLiteral = '\0';
    int literalStart = 0;
    std::string literal;

    bool addSpace = false;

    for (int i = 0; i < line.size(); i++)
    {
        char c = line[i];

        // String or character literal
        if ((c == '"' || c == '\'' || c == '`') && !isEscaped(line, i) && (!inLiteral || c == inLiteral))
        {
            _addSpace(clean, addSpace);
            literal += c;

            if (inLiteral)
            {
                inLiteral = c;
                literalStart = i;
            }
            else
            {
                inLiteral = '\0';
                clean += addLiteral(m_literals, Literal(literal, LiteralType::String));
                literal.clear();
            }
        }
        // Characters inside a string or character literal
        else if (inLiteral)
        {
            literal += c;
        }
        // Whitespace outside of a string literal
        else if (isWhitespace(c))
        {
            addSpace = true;
        }
        // Beginning of a comment
        else if (c == '/' && line.size() > i + 1 && line[i + 1] == '/')
        {
            break;
        }
        else
        {
            _addSpace(clean, addSpace);
            clean += c;
        }
    }

    // Multi-line string literals are illegal
    if (inLiteral)
    {
        throw std::runtime_error("Unexpected end of line (missing string termination)");
    }

    // Skip empty lines
    if (clean.size())
    {
        // Generate a CodeLine object from the line and its metadata and store it
        m_lines.push_back(CodeLine(origin, number, clean, getIndentation(line)));
    }
}
