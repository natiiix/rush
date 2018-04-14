#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <cstdio>

#define TMP_PATH "rush_tmp.cpp"

int main(int argc, char *argv[])
{
    std::ofstream tmpFile(TMP_PATH);

    if (tmpFile.is_open())
    {
        for (int i = 1; i < argc; i++)
        {
            std::cout << "Reading source file: " << argv[i] << std::endl;
            std::ifstream sourceFile(argv[i]);

            if (sourceFile.is_open())
            {
                std::string line;
                while (std::getline(sourceFile, line))
                {
                    tmpFile << line << std::endl;
                }
            }
        }

        tmpFile.close();
        system("c++ -o rush_output.exe " TMP_PATH);
        remove(TMP_PATH);
    }

    return 0;
}
