#pragma once
#include "../Scanning/Token.hpp"
#include "ParseError.hpp"
#include "Expressions.hpp"
#include <vector>
#include "Statements.hpp"

class Parser
{
    std::vector<Token> tokens;
    int current = 0;
public:
    Parser(const std::vector<Token>& tokens) : tokens{tokens} {}
    std::vector<Stmt*> operator()();
private:
    Expr* expression();
    Stmt* declaration();
    Stmt* statement();
    Stmt* ifStatement();
    Stmt* printStatement();
    Stmt* varDeclaration();
    Stmt* whileStatement();
    Stmt* expressionStatement();
    std::vector<Stmt*> block();
    Expr* assignment();
    Expr* logicalOr();
    Expr* logicalAnd();
    Expr* equality();
    Expr* comparison();
    Expr* term();
    Expr* factor();
    Expr* unary();
    Expr* primary();
    // utilities
    bool match(std::initializer_list<TokenType> types);
    bool check(TokenType type);
    Token advance();
    bool isAtEnd();
    Token peek();
    Token previous();
    ParseError error(const Token& token, const std::string& message);
    void synchronize();
    Token consume(TokenType type, const std::string& message);
};