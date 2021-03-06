#include "Literal.hpp"

Literal::Literal(const std::string value, const LiteralType type) : m_value(value), m_type(type)
{
}

const std::string Literal::value(void) const
{
    return m_value;
}

const LiteralType Literal::type(void) const
{
    return m_type;
}
