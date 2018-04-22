#pragma once

#include <string>
#include <vector>
#include <map>

class Compiler
{
  public:
    Compiler(const std::vector<std::string> sourceFiles);
    std::string compile(void) const;

  private:
    std::string m_originalCode;
};
