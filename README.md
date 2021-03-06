# Rush
Rush is a WIP programming language based on C++ being currently developed and maintained by [Ivo Meixner (natiiix)](https://github.com/natiiix) under [MIT license](https://github.com/natiiix/rush/blob/master/LICENSE) since 12th April 2018.

This repository contains the compiler for the Rush language.

Please note that since version v1.0.1 the Rush compiler is also written in the Rush language and thus requires an existing version of itself to be compiled.

# Syntax
```
rush <Main Rush Source File> [--keep] [--origin] [--cpp] [C++ Compiler Arguments]
```
## Compiler options
| Option | Description |
| ------------:|:----------- |
| `--keep` | **Keep the C++ file after a successful compilation to binary.**<br><br>This option has no effect if the `--cpp` option is enabled. |
| `--origin` | **Include the origin (source file, line number) of each line in the C++ file.**<br><br>The origin is written as a comment above the respective line.<br>This option is meant to ease the process of locating errors in Rush code. |
| `--cpp` | **Only compile the Rush source code to C++ code.**<br><br>The C++ file will be located in the same directory as the main source file<br>and it will have its name with `.cpp` appended to it<br><br>The C++ code will NOT be compiled to binary.<br>Using the `--keep` option is not necessary.<br><br>This option can be used to generate C++ code,<br>which can be then compiled to binary on a different platform. |
## Output binary file path
To specify the path of the output binary file, you have to use the `-o` option of the C++ compiler (GCC). See the examples below or [the official GCC documentation](https://gcc.gnu.org/onlinedocs/gcc/Overall-Options.html) for more information.
## Examples
Compile into binary file with a name chosen by the C++ compiler (`a.exe` on Windows, `a.out` on Linux) and delete the C++ file.
```
rush HelloWorld.rush
```

Compile into binary file called `HelloWorld.exe`, insert line origin information into the C++ code and keep the C++ file.
```
rush HelloWorld.rush --keep --origin -o HelloWorld.exe
```

Compile into C++ code and keep the C++ file. This C++ file will be called `HelloWorld.rush.cpp` in this example.
```
rush HelloWorld.rush --cpp
```
# Download
The Rush compiler is currently only available for Microsoft Windows.

[Latest binary release of Rush compiler](https://github.com/natiiix/rush/releases/latest)

# Prerequisites
## GCC
**GCC 4.9 or higher is required.** Earlier version of C++ compiler in GCC lack proper implementation of regular expressions.

The binary releases currently available [here on GitHub](https://github.com/natiiix/rush/releases) were compiled using `c++.exe (x86_64-win32-seh-rev0, Built by MinGW-W64 project) 7.3.0`.

For the ideal results please use the latest available version of GCC. Windows users are adised to use [MinGW-w64](https://mingw-w64.org/), more specifically the [MinGW-w64-builds](https://mingw-w64.org/doku.php/download/mingw-builds) pre-built package.

# Rush Languge Support (VS Code extension)
There is an extension available for Visual Studio Code that adds support (currently only syntax highlighting) for the Rush programming language.

You can download it from [Visual Studio Marketplace](https://marketplace.visualstudio.com/items?itemName=natiiix.rush-language-support).
The source code of this extension is available on [GitHub](https://github.com/natiiix/rush-language-support).
