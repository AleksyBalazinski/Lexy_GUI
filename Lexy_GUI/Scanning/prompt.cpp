#include <string>
#include <iostream>
#include <vector>
#include "Scanner.hpp"
#include "Token.hpp"

extern bool hadError;

// prompts for input, delegates to run()
void runPrompt() 
{
    while(true)
    {
        //std::cout << ">> ";
        std::string line;
        std::getline(std::cin, line);
        if(line.empty()) break;
        run(line);
        hadError = false; // reset the flag
    }
}

