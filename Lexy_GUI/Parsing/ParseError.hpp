#pragma once 
#include "../Scanning/Token.hpp"
#include <string>
#include "../Scanning/errorHandler.hpp"
#include <exception>

class ParseError : public std::exception {};