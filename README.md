# file2constexpr
Convert files into header implemented constexpr arrays.\n
NOTE: constexpr std::string is not currently supported by the STL, so strings are const instead.

## How to use
Call "file2constexpr" within the project directory.\n
Or\n
Use it like cmake, where you call within the build folder"\build\file2constexpr .."\n

## How it works
Reads all the files from "src\constexpr\".\n
These are implemented as constexpr std::array<type> in a header file (default output = \include\output.h)

## Commands
--help\n
--name()\n
--inDir()\n
--outDir()\n
..\n
Call them after "file2constexpr" the order doesn't matter

## Goals
Want to be able to store a variety of formats such as images, binaries, and more!

# Developments
##version 0.1
Able to convert simple int, float, string, and bool files.
