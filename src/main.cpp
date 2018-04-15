#include <iostream>
#include <string>
#include <regex>
#include <fstream>
#include <cstring>
#include <cstdio>

#define TMP_PATH "__rush_temp.cpp"

int main(const int argc, const char *const argv[])
{
    // Not enough arguments
    if (argc < 3)
    {
        std::cout << "Expected syntax: rush <Output File> <Source Files>" << std::endl;
        return -1;
    }

    // Open the temporary file
    std::ofstream tmpFile(TMP_PATH);

    // Unable to open the temporary file
    if (!tmpFile.is_open())
    {
        return -1;
    }

    // Iterate through the source files
    for (int i = 2; i < argc; i++)
    {
        const char *fileName = argv[i];

        std::cout << "Reading source file: " << fileName << std::endl;
        std::ifstream sourceFile(fileName);

        if (!sourceFile.is_open())
        {
            std::cerr << "Unable to read source file \"" << fileName << "\"!" << std::endl;
            continue;
        }

        std::string line;
        while (std::getline(sourceFile, line))
        {
            tmpFile << line << std::endl;
        }

        sourceFile.close();
    }

    // Close the temporary file
    tmpFile.close();

    // Compile the temporary file
    std::string compileCmd("c++ -o ");
    compileCmd += argv[1];
    compileCmd += " ";
    compileCmd += TMP_PATH;

    if (system(compileCmd.c_str()))
    {
        return -1;
    }

    // Delete the temporary file
    if (remove(TMP_PATH))
    {
        return -1;
    }

    // OK
    return 0;
}
