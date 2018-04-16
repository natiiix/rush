#include "CodeLine.hpp"
#include "support.hpp"

CodeLine::CodeLine(const std::string line)
{
    m_code = support::trimWhitespace(line, m_indentation);
}

const int CodeLine::indentation() const
{
    return m_indentation;
}

const std::string CodeLine::code() const
{
    return m_code;
}
