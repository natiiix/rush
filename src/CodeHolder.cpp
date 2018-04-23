#include <fstream>
#include "CodeHolder.hpp"

void CodeHolder::loadFile(const std::string path)
{
    m_loadedFiles.push_back(path);
    std::ifstream file(path);

    for (std::string line; getline(file, line);)
    {
        // TODO
    }
}
