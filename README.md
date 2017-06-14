# ABEGE The Red Comet Production

| Linux Build | Windows Build | Code Quality |
|:-----------:|:-------------:|:------------:|
| [![Build Status](https://travis-ci.org/ABEGE-dev/ABEGE.svg?branch=master)](https://travis-ci.org/ABEGE-dev/ABEGE) | [![Build status](https://ci.appveyor.com/api/projects/status/8dq83vr754gpve8r/branch/master?svg=true)](https://ci.appveyor.com/project/ABEGE-dev/abege/branch/master) | [![Codacy Badge](https://api.codacy.com/project/badge/Grade/650e633030644ff1a4373c88615e1bff)](https://www.codacy.com/app/hs1145/ABEGE?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=ABEGE-dev/ABEGE&amp;utm_campaign=Badge_Grade) |

An AI-and-BGM-Embedded-Game-Engine

## Quick Start
* Linux/Mac
  * Open with IDE that supports CMake (e.g. CLion), or
  * Build from command line:
    ```
    mkdir build
    cd build
    cmake ..
    make
    ```
* Windows
  * Open with Visual Studio 2017+, or
  * Generate Visual Studio project for older VS with CMake
    ```
    cmake -G {Target Name}
    ```
    Target names can be found [here](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html#visual-studio-generators)
