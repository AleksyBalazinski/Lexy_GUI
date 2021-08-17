#pragma once
#include "../Scanning/Token.hpp"
#include <exception>

class RunTimeError : std::exception
{
public:
    Token token;
    std::string message;
//public:
    RunTimeError(const Token& token, const std::string& message) : token{token}, message{message} {}
    const char* what() const noexcept override
    {
        return message.c_str();
    }
};