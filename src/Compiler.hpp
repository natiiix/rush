#pragma once

#include <string>
#include <vector>
#include <map>
#include "CodeLine.hpp"
#include "Literal.hpp"

class Compiler
{
public:
  Compiler(const std::string mainSourcePath);
  std::string compile(void) const;

private:
  std::vector<std::string> m_loadedFiles;
  std::vector<std::string> m_includes;
  std::vector<CodeLine> m_lines;
  std::map<std::string, Literal> m_literals;

  void loadFile(const std::string path);
  std::string getCleanCode(const std::string line);
  void processLine(const std::string line, const std::string origin, const int number);
};
