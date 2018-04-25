#include <iostream>
#include <fstream>
#include <string>
#include "support.hpp"
#include "Compiler.hpp"

using namespace support;

int main(const int argc, const char *const argv[])
{
    // Not enough arguments
    if (argc < 3)
    {
        printLnErr("Expected syntax: rush <Output File> <Main Source File> [--keep] [C++ Compiler Arguments]");
        return -1;
    }

    log("Loading source files");

    // Get the main source file's path
    const std::string srcPath = normalizePath(argv[2]);

    // Create a compiler
    const Compiler comp(srcPath);

    ok();

    log("Compiling the source files into a temporary code");

    // Compile the source files into temporary code
    const std::string tempCode = comp.compile();

    // Compile error occurred
    if (tempCode.empty())
    {
        printLnErr("Unable to compile the source files");
        return -1;
    }

    ok();

    // Open the temporary file
    log("Creating a temporary file");

    const std::string tmpPath = srcPath + ".tmp.cpp";

    std::ofstream tmpFile(tmpPath);

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

    ok();

    // Process optional arguments
    bool deleteTmpFile = true;
    std::string compilerArgs;

    for (int i = 3; i < argc; i++)
    {
        std::string arg = argv[i];

        if (i == 3 && arg == "--keep")
        {
            deleteTmpFile = false;
        }
        else
        {
            compilerArgs += " " + wrapInQuotesIfContainsSpace(arg);
        }
    }

    // Compile the temporary file
    log("Compiling the temporary code into a binary executable");

    std::string compileCmd = "c++ -o " + wrapInQuotesIfContainsSpace(argv[1]) + " " + wrapInQuotesIfContainsSpace(tmpPath) + compilerArgs;

    if (system(compileCmd.c_str()))
    {
        printLnErr("Unable to compile the temporary code");
        return -1;
    }

    ok();

    // Delete the temporary file unless the user has specified they want to keep it
    if (deleteTmpFile)
    {
        log("Deleting the temporary file");

        if (remove(tmpPath.c_str()))
        {
            printLnErr("Unable to delete the temporary file");
            return -1;
        }

        ok();
    }
    else
    {
        log("Keeping the temporary file");
        ok();
    }

    // Everything worked correctly
    return 0;
}
