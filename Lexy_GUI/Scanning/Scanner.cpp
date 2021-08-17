#include "Scanner.hpp"
#include <iostream>
#include <memory>
#include "errorHandler.hpp"
#include "generalUtilities.hpp"
#include "../Parsing/Parser.hpp"
#include "../Parsing/Interpreter.hpp"

extern bool hadError;
extern bool hadRuntimeError;

extern std::string programOutput;

void run(const std::string& source) // runs scanner, prints the result
{
    Scanner scanner{source};
    std::vector<Token> tokens = scanner();

    Parser parser{tokens};
    std::vector<Stmt*> statements = parser();

    if(hadError) 
    {
        return;
    }

    Interpreter interpreter;
    interpreter.interpret(statements); // fills in programOutput

    for(Stmt* statement : statements) 
        delete statement;
}

void Scanner::scanToken()
{
    char c = advance();
    switch(c)
    {
        // single character tokens
        case '(': addToken(TokenType::LEFT_PAREN); break;
        case ')': addToken(TokenType::RIGHT_PAREN); break;
        case '{': addToken(TokenType::LEFT_BRACE); break;
        case '}': addToken(TokenType::RIGHT_BRACE); break;
        case ',': addToken(TokenType::COMMA); break;
        case '.': addToken(TokenType::DOT); break;
        case '-': addToken(TokenType::MINUS); break;
        case '+': addToken(TokenType::PLUS); break;
        case ';': addToken(TokenType::SEMICOLON); break;
        case '*': addToken(TokenType::STAR); break;
        case '/': // comment or SLASH
            if(match('/'))
            {
                while(peek() != '\n' && !isAtEnd()) advance();
            }
            else
            {
                addToken(TokenType::SLASH);
            }
            break;
        // one or two character tokens
        case '!':
            addToken(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
            break;
        case '=':
            addToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
            break;
        case '<':
            addToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
            break;
        case '>':
            addToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
            break;
        // white characters
        case ' ':
        case '\r':
        case '\t':
            break;
        case '\n': line++; break;
        // string literals
        case '"': string(); break;
        

        default: 
            if (utils::isDigit(c)) number();
            else if(utils::isAlpha(c)) identifier();
            else error(line, "Unexpected character!"); break;
    }
}

void Scanner::addToken(TokenType type)
{
    addToken(type, GenVal{});
}

void Scanner::addToken(TokenType type, const GenVal& literal)
{
    std::string text = source.substr(start, current - start);
    tokens.push_back(Token{type, text, GenVal{literal}, line});
}

char Scanner::advance()
{
    return source.at(current++);
}

bool Scanner::match(char expected)
{
    if(isAtEnd()) return false;
    if(source.at(current) != expected) return false;

    current++;
    return true;
}

char Scanner::peek() // lokkahead
{
    if(isAtEnd()) return '\0';
    return source.at(current);
}

void Scanner::number()
{
    while(utils::isDigit(peek())) advance();
    if(peek() == '.' && utils::isDigit(peekNext())) 
    {
        advance();
        while(utils::isDigit(peek())) advance();
    }
    addToken(TokenType::NUMBER, std::stod(source.substr(start, current - start)));
}

void Scanner::identifier()
{
    while(utils::isAlphaNumeric(peek())) advance();

    std::string text = source.substr(start, current - start);
    TokenType type;
    try {type = keywords.at(text);}
    catch(std::out_of_range) {type = TokenType::IDENTIFIER;}
    if(type == TokenType::TRUE) {addToken(type, GenVal{true}); return;}
    if(type == TokenType::FALSE) {addToken(type, GenVal{false}); return;}
    addToken(type);
}

void Scanner::string()
{
    while(peek() != '"' && !isAtEnd())
    {
        if(peek() == '\n') line++;
        advance();
    }
    if(isAtEnd())
    {
        error(line, "Unterminated string!");
        return;
    }
    advance();
    std::string value = source.substr(start + 1, current - 2 - start);
    addToken(TokenType::STRING, value);
}

char Scanner::peekNext()
{
    if(current + 1 >= source.length()) return '\0';
    return source.at(current + 1);
}

std::unordered_map<std::string, TokenType> Scanner::keywords 
{
    {"and", TokenType::AND},
    {"class", TokenType::CLASS},
    {"else", TokenType::ELSE},
    {"false", TokenType::FALSE},
    {"for", TokenType::FOR},
    {"fun", TokenType::FUN},
    {"if", TokenType::IF},
    {"nil", TokenType::NIL},
    {"or", TokenType::OR},
    {"print", TokenType::PRINT},
    {"return", TokenType::RETURN},
    {"super", TokenType::SUPER},
    {"this", TokenType::THIS},
    {"true", TokenType::TRUE},
    {"var", TokenType::VAR},
    {"while", TokenType::WHILE}
};

std::vector<Token> Scanner::operator()()
{
    while(!isAtEnd())
    {
        start = current;
        scanToken();
    }
    tokens.push_back(Token{TokenType::END_OF_FILE, "", GenVal{}, line});
    return tokens;
}


