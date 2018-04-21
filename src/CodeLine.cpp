#include "CodeLine.hpp"
#include "support.hpp"

CodeLine::CodeLine(const std::string code, const int indentation) : m_code(code), m_indentation(indentation)
{
}

const int CodeLine::indentation() const
{
    return m_indentation;
}

const std::string CodeLine::code() const
{
    return m_code;
}
