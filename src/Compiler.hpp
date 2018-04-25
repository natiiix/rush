#pragma once

#include <string>
#include <vector>
#include "CodeLine.hpp"

class Compiler
{
public:
  Compiler(const std::string mainSourcePath);
  std::string compile(void) const;

private:
  std::vector<std::string> m_loadedFiles;
  std::vector<std::string> m_includes;
  std::vector<CodeLine> m_lines;

  void loadFile(const std::string path);
};
