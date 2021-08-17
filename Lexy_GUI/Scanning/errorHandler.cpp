#include "errorHandler.hpp"
#include <string>
#include <iostream>

extern bool hadError;
extern bool hadRuntimeError; 
extern std::string programOutput;

void report(int line, const std::string& where, const std::string& message)
{
    programOutput += "[line " + std::to_string(line) + "] Error" + where + ": " + message + '\n';
    hadError = true;
}

void error(int line, const std::string& message)
{
    report(line, "", message);
}

void error(const Token& token, const std::string& message)
{
    if(token.type == TokenType::END_OF_FILE)
    {
        report(token.line, " at end", message);
    }
    else
    {
        report(token.line, " at \'" + token.lexeme + "\'", message);
    }
}

void runTimeError(const RunTimeError& error)
{
    programOutput += std::string{error.what()} + "\n[line " + std::to_string(error.token.line) + "]\n";
    hadRuntimeError = true;
}
