#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <cstdio>

#define TMP_PATH "rush_tmp.cpp"

int main(int argc, char *argv[])
{
    // Open the temporary file
    std::ofstream tmpFile(TMP_PATH);

    // Unable to open the temporary file
    if (!tmpFile.is_open())
    {
        return -1;
    }

    // Iterate through the source files
    for (int i = 1; i < argc; i++)
    {
        std::cout << "Reading source file: " << argv[i] << std::endl;
        std::ifstream sourceFile(argv[i]);

        if (!sourceFile.is_open())
        {
            std::cerr << "Unable to read source file \"" << argv[1] << "\"!" << std::endl;
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
    if (system("c++ -o rush_output.exe " TMP_PATH))
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
