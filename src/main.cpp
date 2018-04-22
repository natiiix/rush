#include <iostream>
#include <fstream>
#include <string>
#include "support.hpp"
#include "compiler.hpp"

using namespace support;

#define TMP_PATH "__rush_temp.cpp"

void log(const char *const str)
{
    std::cout << str << " ... ";
}

int main(const int argc, const char *const argv[])
{
    // Not enough arguments
    if (argc < 3)
    {
        printLnErr("Expected syntax: rush <Output File> <Source Files>");
        return -1;
    }

    // Create a vector to hold the code from the source files
    std::vector<std::string> sourceFiles;

    // Read the source files
    for (int i = 2; i < argc; i++)
    {
        const char *const path = argv[i];

        std::cout << "Reading source file: " << path << " ... ";
        std::string code = readFile(path);

        if (code.empty())
        {
            printLnErr("Unable to read source file / source file is empty");
            return -1;
        }
        else
        {
            printLn("OK");
            sourceFiles.push_back(code);
        }
    }

    // Compile the source files into temporary code
    log("Compiling the source files into a temporary code");

    Compiler comp(sourceFiles);
    std::string tempCode = comp.compile();

    // Compile error occurred
    if (tempCode.empty())
    {
        printLnErr("Unable to compile the source files");
        return -1;
    }

    printLn("OK");

    // Open the temporary file
    log("Creating a temporary file");

    std::ofstream tmpFile(TMP_PATH);

    // Check if the temporary file has been correctly opened
    if (!tmpFile.is_open())
    {
        printLnErr("Unable to create a temporary file");
        return -1;
    }

    // Write the temporary code to the temporary file
    tmpFile << tempCode;

    // Close the temporary file
    tmpFile.close();

    printLn("OK");

    // Compile the temporary file
    log("Compiling the temporary code into a binary executable");

    std::string compileCmd("c++ -o ");
    compileCmd += argv[1];
    compileCmd += " ";
    compileCmd += TMP_PATH;

    if (system(compileCmd.c_str()))
    {
        printLnErr("Unable to compile the temporary code");
        return -1;
    }

    printLn("OK");

    // Delete the temporary file
    // log("Deleting the temporary file");

    // if (remove(TMP_PATH))
    // {
    //     printLnErr("Unable to delete the temporary file");
    //     return -1;
    // }

    // printLn("OK");

    // Everything worked correctly
    return 0;
}
