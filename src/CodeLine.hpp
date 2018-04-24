#pragma once

#include <string>

struct CodeLine
{
public:
  CodeLine(const std::string origin, const int number, const std::string code, const int indentation);

  // Source file
  const std::string origin;
  // Line number in source file
  const int number;
  // Code on the line (without leading and trailing whitespace)
  const std::string code;
  // Number of leading whitespace characters
  const int indentation;
};
