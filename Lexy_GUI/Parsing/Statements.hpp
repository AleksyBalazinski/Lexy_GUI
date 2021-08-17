#pragma once
#include <iostream>
#include "Expressions.hpp"
#include <vector>

// Uses the Visitor Design Pattern

class AbstractDispatcherStmt;

class Stmt 
{
public:
    virtual void accept(AbstractDispatcherStmt*) = 0;
    virtual ~Stmt()
    {
    }
};

class Block;
class Expression;
class If;
class Print;
class Var;
class While;

class AbstractDispatcherStmt 
{
public:
    virtual void dispatch(Block*) = 0;
    virtual void dispatch(Expression*) = 0;
    virtual void dispatch(If*) = 0;
    virtual void dispatch(Print*) = 0;
    virtual void dispatch(Var*) = 0;
    virtual void dispatch(While*) = 0;
};

class Block : public Stmt
{
public:
    std::vector<Stmt*> statements;
//public:
    Block(const std::vector<Stmt*>& statements) : statements{statements} {}
    ~Block() override
    {
        for(Stmt* statement : statements) 
            delete statement;
    }
    void accept(AbstractDispatcherStmt* d) override
    {
        d->dispatch(this);
    }
};

class Expression : public Stmt
{
public:
    Expr* expression;
//public:
    Expression(Expr* expression) : expression{expression} {}
    ~Expression() override
    {
        delete expression;
    }
    void accept(AbstractDispatcherStmt* d) override
    {
        d->dispatch(this);
    }
};

class If : public Stmt
{
public:
    Expr* condition;
    Stmt* thenBranch;
    Stmt* elseBranch;
//public:
    If(Expr* condition, Stmt* thenBranch, Stmt* elseBranch)
        : condition{condition}, thenBranch{thenBranch}, elseBranch{elseBranch} {} // DEBUG
    ~If()
    {
        delete condition; 
        delete thenBranch;
        delete elseBranch;
    }
    void accept(AbstractDispatcherStmt* d) override
    {
        d->dispatch(this);
    }
};

class Print : public Stmt
{
public:
    Expr* expression;
//public:
    Print(Expr* expression) : expression{expression} {}
    ~Print() override
    {
        delete expression;
    }
    void accept(AbstractDispatcherStmt* d) override
    {
        d->dispatch(this);
    }
};

class Var : public Stmt
{
public:
    Token name;
    Expr* initializer;
//public:
    Var(Token name, Expr* initializer) : name{name}, initializer{initializer} {}
    ~Var() override
    {
        delete initializer;
    }
    void accept(AbstractDispatcherStmt* d) override
    {
        d->dispatch(this);
    }
};

class While : public Stmt
{
public:
    Expr* condition;
    Stmt* body;
//public:
    While(Expr* condition, Stmt* body) : condition{condition}, body{body} {} // DEBUG
    ~While() override
    {
        delete condition;
        delete body;
    }
    void accept(AbstractDispatcherStmt* d) override
    {
        d->dispatch(this);
    }
};
