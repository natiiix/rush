#include <iostream>
#include <fstream>
#include <string>
#include "support.hpp"
#include "Compiler.hpp"

using namespace support;

int main(const int argc, const char *const argv[])
{
    // Not enough arguments
    if (argc != 3)
    {
        printLnErr("Expected syntax: rush <Output File> <Main Source File>");
        return -1;
    }

    // Create a compiler
    Compiler comp(normalizePath(argv[2]));

    // Compile the source files into temporary code
    log("Compiling the source files into a temporary code");

    std::string tempCode = comp.compile();

    // Compile error occurred
    if (tempCode.empty())
    {
        printLnErr("Unable to compile the source files");
        return -1;
    }

    ok();

    // Open the temporary file
    log("Creating a temporary file");

    const std::string tmpPath = "__rush_temp.cpp";

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

    // Compile the temporary file
    log("Compiling the temporary code into a binary executable");

    std::string compileCmd = "c++ -o " + std::string(argv[1]) + " " + tmpPath;

    if (system(compileCmd.c_str()))
    {
        printLnErr("Unable to compile the temporary code");
        return -1;
    }

    ok();

    // Delete the temporary file
    // log("Deleting the temporary file");

    // if (remove(tmpPath.c_str()))
    // {
    //     printLnErr("Unable to delete the temporary file");
    //     return -1;
    // }

    // ok();

    // Everything worked correctly
    return 0;
}
