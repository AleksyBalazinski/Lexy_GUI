#pragma once
#include <string>
#include <ostream>
#include "GenVal.hpp"
#include "generalUtilities.hpp"


enum class TokenType
{
    // single character tokens
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
    COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,
    // one or two character tokens
    BANG, BANG_EQUAL, 
    EQUAL, EQUAL_EQUAL,
    GREATER, GREATER_EQUAL,
    LESS, LESS_EQUAL,
    // literals
    IDENTIFIER, STRING, NUMBER,
    // keywords
    AND, CLASS, ELSE, FALSE, TRUE, FUN, FOR, IF, NIL, OR, 
    PRINT, RETURN, SUPER, THIS, VAR, WHILE,

    END_OF_FILE
};

class Token
{
public:
    TokenType type;
    std::string lexeme;
    GenVal literal;
    int line;
//public:
    Token(TokenType type, std::string lexeme, GenVal literal, int line)
        : type{type}, lexeme{lexeme}, literal{literal}, line{line} {}
    
    friend std::ostream& operator<<(std::ostream& out, const Token& t);
};

