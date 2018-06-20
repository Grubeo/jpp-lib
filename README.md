# jpp-lib - development version
Target is the most performance library for parsing json files in the world for C++ hardcore-optimization fans. 
This library is **under development** so coding style, file structure and everything else **may change**.

## Goals of this project
* usage of STL-like iterators for input and output
* convinient functions to provide nice loooking usecases
* fast runtime usage
* (distant future) constexpr modeling of JSON structure for quick loading of application settings

## Compilation
Just run compile.js script in [nodejs](https://nodejs.org/en/). That will build all modules to *.o files and an current development example about this library.

## Requiments
* g++ supporting C++17 (std::variant for example)
* optional: nodejs for auto-compiling and POSIX system for example io_handling
