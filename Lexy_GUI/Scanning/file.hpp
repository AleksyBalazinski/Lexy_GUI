#pragma once
#include <iostream>
#include <fstream>
#include <streambuf>
#include "Scanner.hpp"

extern bool hadError;
extern bool hadRuntimeError;

void runFile(const char* path)
{
    std::ifstream file{path};
    std::string contents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    run(contents);
    if(hadError) exit(65);
    if(hadRuntimeError) exit(70);
}
