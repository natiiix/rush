#pragma once

#include <string>

class CodeLine
{
public:
  CodeLine(const std::string code, const int indentation);

  const int indentation() const;
  const std::string code() const;

private:
  int m_indentation;
  std::string m_code;
};
