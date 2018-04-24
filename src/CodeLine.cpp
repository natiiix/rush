#include "CodeLine.hpp"
#include "support.hpp"

using namespace support;

CodeLine::CodeLine(const std::string origin, const int number, const std::string line) : origin(origin), number(number), code(trimWhitespace(line)), indentation(getIndentation(line))
{
}
