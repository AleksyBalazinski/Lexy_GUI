#pragma once
#include <unordered_map>
#include <string>
#include "../Scanning/GenVal.hpp"
#include "../Scanning/Token.hpp"
#include "RunTimeError.hpp"

class Environment
{
    std::unordered_map<std::string, GenVal> values;
public:
    void define(std::string name, GenVal value)
    {
        values.insert({name, value});
    }
    GenVal get(Token name)
    {
        try
        {
            return values.at(name.lexeme);
        }
        catch(std::out_of_range)
        {
            throw RunTimeError{name, "Undefinde variable \'" + name.lexeme + "\'."};
        }
    }
    void assign(Token name, GenVal value)
    {
        try
        {
            values.at(name.lexeme) = value;
            return;
        }
        catch(std::out_of_range)
        {
            throw RunTimeError{name, "Undefined variable \'" + name.lexeme + "\'."};
        }
    }
};