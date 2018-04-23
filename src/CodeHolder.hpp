#pragma once

#include <vector>
#include <string>
#include "CodeLine.hpp"

class CodeHolder
{
  public:
    void loadFile(const std::string path);

  private:
    std::vector<std::string> m_loadedFiles;
    std::vector<CodeLine> m_lines;
};
