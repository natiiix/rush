#include "CodeLine.hpp"
#include "support.hpp"

using namespace support;

CodeLine::CodeLine(const std::string origin, const int number, const std::string code, const int indentation) : origin(origin), number(number), code(code), indentation(indentation)
{
}
