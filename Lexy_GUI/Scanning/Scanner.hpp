#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "Token.hpp"

void run(const std::string& source);

class Scanner
{
    std::string source;
    std::vector<Token> tokens;
    std::string::size_type start = 0, current = 0, line = 1;
    void scanToken();
    void addToken(TokenType type);
    void addToken(TokenType type, const GenVal& literal);
    char advance();
    bool match(char expected);
    char peek();
    void number();
    void identifier();
    void string();
    char peekNext();
    bool isAtEnd() {return current >= source.length();}
    static std::unordered_map<std::string, TokenType> keywords;
public:
    Scanner(const std::string& source) : source{source} {}
    std::vector<Token> operator()();
};
