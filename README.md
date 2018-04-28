# Rush
Rush is a WIP programming language based on C++ being currently developed and maintained by [Ivo Meixner (natiiix)](https://github.com/natiiix) under [MIT license](https://github.com/natiiix/rush/blob/master/LICENSE) since 12th April 2018.

This repository contains the compiler for the Rush language.

Please note that since version v1.0.1 the Rush compiler is also written in the Rush language and thus requires an existing version of itself to be compiled.

# Syntax
```
rush <Output File> <Main Source File> [--keep] [C++ Compiler Arguments]
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
