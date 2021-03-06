#pragma once

#include <string>

enum LiteralType
{
  Number,
  String
};

class Literal
{
public:
  Literal(void) {}
  Literal(const std::string value, const LiteralType type);

  const std::string value(void) const;
  const LiteralType type(void) const;

private:
  std::string m_value;
  LiteralType m_type;
};
