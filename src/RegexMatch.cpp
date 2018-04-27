#include "RegexMatch.hpp"

RegexMatch::RegexMatch(const std::smatch m)
{
    m_position = m.position();
    m_length = m.length();
    m_str = m.str();
    m_prefix = m.prefix();
    m_suffix = m.suffix();

    m_empty = m.empty();
    m_size = m.size() - 1;
    m_captures = std::vector<std::string>(m.begin() + 1, m.end());
}

const bool RegexMatch::success() const
{
    return !m_empty;
}

const int RegexMatch::position() const
{
    return m_position;
}

const int RegexMatch::length() const
{
    return m_length;
}

const std::string RegexMatch::str() const
{
    return m_str;
}

const std::string RegexMatch::prefix() const
{
    return m_prefix;
}

const std::string RegexMatch::suffix() const
{
    return m_suffix;
}

const bool RegexMatch::empty() const
{
    return m_empty;
}

const int RegexMatch::size() const
{
    return m_size;
}

const std::string RegexMatch::operator[](const int n) const
{
    return m_captures[n];
}

const std::vector<std::string> RegexMatch::captures() const
{
    return m_captures;
}

const std::vector<std::string>::const_iterator RegexMatch::begin() const
{
    return m_captures.begin();
}

const std::vector<std::string>::const_iterator RegexMatch::end() const
{
    return m_captures.end();
}
