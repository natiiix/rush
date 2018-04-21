#include <iostream>
#include <regex>
#include "compiler.hpp"
#include "support.hpp"
#include "CodeLine.hpp"

using namespace support;

std::string compile(const std::vector<std::string> sourceFiles)
{
    std::vector<CodeLine> lines;

    for (std::string file : sourceFiles)
    {
        // Remove carriage returns, split on new line
        for (std::string line : split(replaceAll(file, "\r", std::string()), "\n"))
        {
            int indentation;
            std::string code = trimWhitespace(line, indentation);

            // Ignore empty lines
            if (!code.empty())
            {
                lines.push_back(CodeLine(code, indentation));
            }
        }
    }

    // TODO: Process the code lines

    // Concentrate the lines together
    std::string compiled;

    for (CodeLine line : lines)
    {
        compiled += line.code();
        compiled += '\n';
    }

    return compiled;
}
