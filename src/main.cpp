#include <iostream>
#include <fstream>
#include <string>
#include "support.hpp"
#include "compiler.hpp"

using namespace support;

#define TMP_PATH "__rush_temp.cpp"

int main(const int argc, const char *const argv[])
{
    // std::string str("Hello <Tag> World! <AnotherTag> Ooops! <ThirdTag>");
    // // std::smatch mr;
    // std::regex reg("<(\\w+)>");

    // std::vector<RegexMatch> matches = getAllMatches(reg, str);

    // // if (std::regex_search(str, mr, reg))
    // // {
    // //     printLn("Match!");
    // // }
    // // else
    // // {
    // //     printLn("Not a match!");
    // // }

    // std::cout << "Found " << matches.size() << " matches!" << std::endl;

    // int n = 0;
    // for (RegexMatch mr : matches)
    // {
    //     std::cout << "-- Match number " << ++n << std::endl;

    //     std::cout
    //         << "Empty: " << mr.empty()
    //         << " Size: " << mr.size()
    //         << " Prefix: " << mr.prefix()
    //         << " Suffix: " << mr.suffix()
    //         << " Length: " << mr.length()
    //         << " Position: " << mr.position()
    //         << " Str: " << mr.str() << std::endl;

    //     std::for_each(mr.begin(), mr.end(), [](const std::string x) -> void { printLn(x); });
    // }

    // return 0;

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

        std::cout << "Reading source file: " << path << std::endl;
        std::string code = readFile(path);

        if (code.empty())
        {
            printLnErr("Unable to read source file / source file is empty");
            return -1;
        }
        else
        {
            sourceFiles.push_back(code);
        }
    }

    // Compile the source files into temporary code
    std::string tempCode = compile(sourceFiles);

    // Open the temporary file
    std::ofstream tmpFile(TMP_PATH);

    // Unable to open the temporary file
    if (!tmpFile.is_open())
    {
        printLnErr("Unable to create a temporary file");
        return -1;
    }

    // Write the temporary code to the temporary file
    tmpFile << tempCode;

    // Close the temporary file
    tmpFile.close();

    // Compile the temporary file
    std::string compileCmd("c++ -o ");
    compileCmd += argv[1];
    compileCmd += " ";
    compileCmd += TMP_PATH;

    printLn("Compiling temporary code...");

    if (system(compileCmd.c_str()))
    {
        printLnErr("Unable to compile the temporary code");
        return -1;
    }

    // Delete the temporary file
    if (remove(TMP_PATH))
    {
        printLnErr("Unable to delete the temporary file");
        return -1;
    }

    // Everything worked correctly
    printLn("OK");
    return 0;
}
