#pragma once
#include <string>
#include "Token.hpp"
#include "../Parsing/RunTimeError.hpp"

void error(int line, const std::string& message);
void report(int line, const std::string& where, const std::string& message);
void error(const Token& token, const std::string& message);
void runTimeError(const RunTimeError& error);