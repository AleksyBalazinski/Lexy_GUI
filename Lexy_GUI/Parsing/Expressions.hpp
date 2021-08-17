#pragma once
#include "../Scanning/Token.hpp"
#include <string>
#include <initializer_list>
#include <iostream>

// Uses the visitor design pattern

class AbstractDispatcher;

class Expr
{
public:
    virtual void accept(AbstractDispatcher*) = 0;
    virtual ~Expr() 
    {
    }
};

class Literal;
class Logical;
class Unary;
class Binary;
class Grouping;
class Variable;
class Assign;

class AbstractDispatcher
{
public:
    virtual void dispatch(Literal*) = 0;
    virtual void dispatch(Logical*) = 0;
    virtual void dispatch(Unary*) = 0;
    virtual void dispatch(Binary*) = 0;
    virtual void dispatch(Grouping*) = 0;
    virtual void dispatch(Variable*) = 0;
    virtual void dispatch(Assign*) = 0;
};

class Literal : public Expr
{
public:
    GenVal value;
//public:
    Literal(GenVal value) : value{value} {}
    ~Literal() override 
    {
    }
    void accept(AbstractDispatcher* d) override
    {
        d->dispatch(this);
    }
};

class Logical : public Expr
{
public:
    Expr* left;
    Token op; // operator
    Expr* right;
//public
    Logical(Expr* left, Token op, Expr* right) : left{left}, op{op}, right{right} {}
    ~Logical() override
    {
        delete left; 
        delete right;
    }
    void accept(AbstractDispatcher* d) override
    {
        d->dispatch(this);
    }
};

class Unary : public Expr
{
public:
    Token op; // operator
    Expr* right;
//public:
    Unary(Token op, Expr* right) : op{op}, right{right} {}
    ~Unary() override
    {
        delete right;
    }
    void accept(AbstractDispatcher* d) override
    {
        d->dispatch(this);
    }
};

class Binary : public Expr
{
public:
    Expr* left;
    Token op;
    Expr* right;
//public:
    Binary(Expr* left, Token op, Expr* right)
    : left{left}, op{op}, right{right} {}
    ~Binary() override
    {
        delete left;
        delete right;
    }
    void accept(AbstractDispatcher* d) override
    {
        d->dispatch(this);
    }
};

class Grouping : public Expr
{
public:
    Expr* expression; //Expr expression;
//public:
    Grouping(Expr* expression) : expression{expression} {}
    ~Grouping() override
    {
        delete expression;
    }
    void accept(AbstractDispatcher* d) override
    {
        d->dispatch(this);
    }
};

class Variable : public Expr
{
public:
    Token name;
// public:
    Variable(Token name) : name{name} {}
    ~Variable() override
    {
    }
    void accept(AbstractDispatcher* d) override
    {
        d->dispatch(this);
    }
};

class Assign : public Expr
{
public:
    Token name;
    Expr* value;
//public:
    Assign(Token name, Expr* value) : name{name}, value{value} {}
    ~Assign() override
    {
        delete value;
    }
    void accept(AbstractDispatcher* d) override
    {
        d->dispatch(this);
    }
};
