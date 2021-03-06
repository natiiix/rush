#pragma once

#include <regex>
#include <string>
#include <vector>

class RegexMatch
{
public:
  RegexMatch(const std::smatch m);

  const bool success() const;
  const int position() const;
  const int length() const;
  const std::string str() const;
  const std::string prefix() const;
  const std::string suffix() const;

  const bool empty() const;
  const int size() const;
  const std::string operator[](const int n) const;
  const std::vector<std::string> captures() const;
  const std::vector<std::string>::const_iterator begin() const;
  const std::vector<std::string>::const_iterator end() const;

private:
  int m_position;
  int m_length;
  std::string m_str;
  std::string m_prefix;
  std::string m_suffix;

  bool m_empty;
  int m_size;
  std::vector<std::string> m_captures;
};
