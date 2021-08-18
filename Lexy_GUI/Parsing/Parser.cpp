#include "Parser.hpp"
#include "ParseError.hpp"
#include <vector>

std::vector<Stmt*> Parser::operator()()
{
    std::vector<Stmt*> statements;
    while(!isAtEnd())
    {
        statements.push_back(declaration());
    }

    return statements;
}

Expr* Parser::expression()
{
    return assignment();
}

Stmt* Parser::declaration()
{
    try
    {
        if(match({TokenType::VAR})) return varDeclaration();

        return statement();
    }
    catch(ParseError& error)
    {
        synchronize();
         
        return nullptr;
    }
}

Stmt* Parser::statement()
{
    if(match({TokenType::IF})) return ifStatement();
    if(match({TokenType::PRINT})) return printStatement();
    if(match({TokenType::WHILE})) return whileStatement();
    if(match({TokenType::LEFT_BRACE})) return new Block{block()};
    return expressionStatement();
}

Stmt* Parser::ifStatement()
{
    consume(TokenType::LEFT_PAREN, "Expect \'(\' after \'if\'.");
    Expr* condition = expression();
    try
    {
        consume(TokenType::RIGHT_PAREN, "Expect \')\' after if condition.");
    }
    catch(ParseError&)
    {
        delete condition;
        throw;
    }

    Stmt* thenBranch = statement();
    Stmt* elseBranch = nullptr;
    if(match({TokenType::ELSE}))
        elseBranch = statement();
    
    return new If{condition, thenBranch, elseBranch};
}

Stmt* Parser::printStatement()
{
    Expr* value = expression();
    try
    {
        consume(TokenType::SEMICOLON, "Expect \';\' after value.");
    }
    catch(ParseError&)
    {
        delete value;
        throw; // rethrow
    }
    return new Print{value};
}

Stmt* Parser::varDeclaration()
{
    Token name = consume(TokenType::IDENTIFIER, "Expect variable name.");

    Expr* initializer = nullptr;
    if(match({TokenType::EQUAL})) initializer = expression();
    try
    {
    consume(TokenType::SEMICOLON, "Expect \';\' after variable declaration.");
    }
    catch(ParseError&)
    {
        delete initializer;
        throw;
    }
    return new Var{name, initializer};
}

Stmt* Parser::whileStatement()
{
    consume(TokenType::LEFT_PAREN, "Expect \'(\' after \'while\'.");
    Expr* condition = expression();
    try
    {
        consume(TokenType::RIGHT_PAREN, "Expect \')\' after condition.");
    }
    catch(ParseError&)
    {
        delete condition;
        throw; // rethrow
    }
    Stmt* body = statement();

    return new While{condition, body};
}

Stmt* Parser::expressionStatement()
{
    Expr* expr = expression();
    try
    {
        consume(TokenType::SEMICOLON, "Expect \';\' after expression.");
    }
    catch(ParseError&)
    {
        delete expr;
        throw; // rethrow
    }

    return new Expression{expr};
}

std::vector<Stmt*> Parser::block()
{
    std::vector<Stmt*> statements;
    while(!check(TokenType::RIGHT_BRACE) && !isAtEnd())
    {
        statements.push_back(declaration());
    }
    try
    {
        consume(TokenType::RIGHT_BRACE, "Expect \'}\' after block.");
    }
    catch(ParseError&)
    {
        for(Stmt* statement : statements) delete statement;
        throw; // rethrow
    }
    return statements;
}

Expr* Parser::assignment()
{
    Expr* expr = logicalOr();

    if(match({TokenType::EQUAL}))
    {
        Token equals = previous();
        Expr* value = assignment();
    
        if(dynamic_cast<Variable*>(expr) != nullptr)
        {
            Token name = dynamic_cast<Variable*>(expr)->name;
            return new Assign{name, value};
        }

        error(equals, "Invalid assignment target.");
    }

    return expr;
}

Expr* Parser::logicalOr()
{
    Expr* expr = logicalAnd();

    while(match({TokenType::OR}))
    {
        Token op = previous();
        Expr* right = logicalAnd();
        expr = new Logical{expr, op, right};
    }

    return expr;
}

Expr* Parser::logicalAnd()
{
    Expr* expr = equality();

    while(match({TokenType::AND}))
    {
        Token op = previous();
        Expr* right = equality();
        expr = new Logical{expr, op, right};
    }

    return expr;
}

Expr* Parser::equality()
{
    Expr* expr = comparison();

    while(match({TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL}))
    {
        Token op = previous();
        Expr* right = comparison();
        expr = new Binary{expr, op, right};
    }

    return expr;
}

Expr* Parser::comparison()
{
    Expr* expr = term();

    while(match({TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS, TokenType::LESS_EQUAL}))
    {
        Token op = previous();
        Expr* right = term();
        expr = new Binary{expr, op, right};
    }

    return expr;
}

Expr* Parser::term()
{
    Expr* expr = factor();
    while(match({TokenType::MINUS, TokenType::PLUS}))
    {
        Token op = previous();
        Expr* right = factor();
        expr = new Binary{expr, op, right};
    }

    return expr;
}

Expr* Parser::factor()
{
    Expr* expr = unary();

    while(match({TokenType::SLASH, TokenType::STAR}))
    {
        Token op = previous();
        Expr* right = unary();
        expr = new Binary{expr, op, right};
    }

    return expr;
}

Expr* Parser::unary()
{
    if(match({TokenType::BANG, TokenType::MINUS}))
    {
        Token op = previous();
        Expr* right = unary();
        return new Unary{op, right};
    }

    return primary();
}

Expr* Parser::primary()
{
    if(match({TokenType::FALSE})) return new Literal{GenVal{false}};
    if(match({TokenType::TRUE})) return new Literal{GenVal{true}};
    if(match({TokenType::NIL})) return new Literal{GenVal{nullptr}};
    
    if(match({TokenType::NUMBER, TokenType::STRING}))
    {
        return new Literal{previous().literal};
    }

    if(match({TokenType::IDENTIFIER}))
    {
        return new Variable{previous()};
    }

    if(match({TokenType::LEFT_PAREN}))
    {
        Expr* expr = expression();
        consume(TokenType::RIGHT_PAREN, "Expect \')\' after expression.");
        return new Grouping{expr};
    }

    throw error(peek(), "Expect expression.");
}

// utilities

// checks if any type given in the list corresponds to the type of the current token and advances
bool Parser::match(std::initializer_list<TokenType> types) 
{
    for(TokenType type : types)
    {
        if(check(type))
        {
            advance();
            return true;
        }
    }
    return false;
}

// returns true if the current token is of given type <type>
bool Parser::check(TokenType type) 
{
    if(isAtEnd()) return false;
    return peek().type == type;
}

// consumes the current token and returns it
Token Parser::advance() 
{
    if(!isAtEnd()) current++;
    return previous();
}

// checks if the current token is the final token
bool Parser::isAtEnd() 
{
    return peek().type == TokenType::END_OF_FILE;
}

// returns current token
Token Parser::peek() 
{
    return tokens.at(current);
}

// returns previous token
Token Parser::previous() 
{
    return tokens.at(current - 1);
}

ParseError Parser::error(const Token& token, const std::string& message)
{
    ::error(token, message);
    return ParseError{};
}

void Parser::synchronize()
{
    advance();

    while(!isAtEnd())
    {
        if(previous().type == TokenType::SEMICOLON) return;
        switch(peek().type)
        {
            //case TokenType::CLASS:
            //case TokenType::FUN:
            case TokenType::VAR:
            //case TokenType::FOR:
            case TokenType::IF:
            case TokenType::WHILE:
            case TokenType::PRINT:
            //case TokenType::RETURN:
                return;
            default:
                break;
        }
        advance();
    }

}

// advances, throws ParseError
Token Parser::consume(TokenType type, const std::string& message)
{
    if(check(type)) return advance();
    throw error(peek(), message);
}
