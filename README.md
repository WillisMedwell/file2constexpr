# file2constexpr
Convert files into header implemented constexpr arrays.\
NOTE: constexpr std::string is not currently supported by the STL, so strings are const instead.

## How to use
Call "file2constexpr" within the project directory.\
Or\
Use it like cmake, where you call within the build folder "\build\file2constexpr .."

## How it works
Reads all the files from "src\constexpr\".
These are implemented as constexpr std::array<type> in a header file (default output = \include\output.h)

## Commands
--help\
--name()\
--inDir()\
--outDir()\
..\
Call them after "file2constexpr" the order doesn't matter

## Goals
Want to be able to store a variety of formats such as images, binaries, and more!

# Developments
##version 0.1
Able to convert simple int, float, string, and bool files.
