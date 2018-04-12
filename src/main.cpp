#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <cstdio>

char const *const tmpPath = "rush_tmp.cpp";

void compile(void)
{
    char command[1024];

    strcpy(command, "c++ -o rush_output.exe ");
    strcat(command, tmpPath);

    system(command);
}

int main(int argc, char *argv[])
{
    std::ofstream tmpFile(tmpPath);

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
        compile();
        remove(tmpPath);
    }

    return 0;
}
