#pragma once
#include "Expressions.hpp"
#include <iostream>
#include "RunTimeError.hpp"
#include "../Scanning/errorHandler.hpp"
#include "Statements.hpp"
#include <vector>
#include "Environment.hpp"
#include <cmath>

#include "../mainwindow.h"
#include "../ui_mainwindow.h"

extern std::string programOutput;

// multiple inheritance -- who would have thought!
class Interpreter : public AbstractDispatcher, public AbstractDispatcherStmt 
{
    Environment environment;
    GenVal result;
    GenVal evaluate(Expr* expr);
    void execute(Stmt* stmt) {stmt->accept(this);}
    void executeBlock(const std::vector<Stmt*>& statements);
    bool isTruthy(const GenVal& value);
    bool isEqual(const GenVal& lhs, const GenVal& rhs);
    void checkNumberOperand(const Token& op, const GenVal& operand);
    void checkNumberOperands(const Token& token, const GenVal& lhs, const GenVal& rhs);
public:
    GenVal getResult() const {return result;}
    void interpret(std::vector<Stmt*> statements)
    {
        try
        {   
            for(Stmt* statement : statements)
            {
                execute(statement);
            }
        }
        catch(const RunTimeError& error)
        {
            runTimeError(error);
        }
    }
    // Expr
    void dispatch(Literal* l) override
    {
        if(l->value.type == GenVal::Type::_bool_)
        {
            result.type = GenVal::Type::_bool_;
            result.b = l->value.b;
        }
        if(l->value.type == GenVal::Type::_double_)
        {
            result.type = GenVal::Type::_double_;
            result.d = l->value.d;
        }
        if(l->value.type == GenVal::Type::_null_)
        {
            result.type = GenVal::Type::_null_;
        }
        if(l->value.type == GenVal::Type::_string_)
        {
            result.type = GenVal::Type::_string_;
            result.s = l->value.s;
        }
    }

    void dispatch(Grouping* g) override
    {
        evaluate(g->expression);
    }

    void dispatch(Unary* u) override
    {
        GenVal right = evaluate(u->right);

        switch(u->op.type)
        {
            case TokenType::BANG:
                result.type = GenVal::Type::_bool_;
                result.b = !isTruthy(right);
                return;
            case TokenType::MINUS:
                checkNumberOperand(u->op, right);
                result.type = GenVal::Type::_double_;
                result.d = -(right.d);
                return;
            default:
                break;
        }

        result.type = GenVal::Type::_null_;
    }

    void dispatch(Binary* b)
    {
        GenVal left = evaluate(b->left);
        GenVal right = evaluate(b->right);

        switch(b->op.type)
        {
            // operations
            case TokenType::MINUS:
                checkNumberOperands(b->op, left, right);
                result.type = GenVal::Type::_double_;
                result.d = left.d - right.d;
                return;
            case TokenType::SLASH:
                checkNumberOperands(b->op, left, right);
                result.type = GenVal::Type::_double_;
                result.d = left.d / right.d;
                return;
            case TokenType::STAR:
                checkNumberOperands(b->op, left, right);
                result.type = GenVal::Type::_double_;
                result.d = left.d * right.d;
                return;
            case TokenType::PERCENT:
                checkNumberOperands(b->op, left, right);
                result.type = GenVal::Type::_double_;
                result.d = static_cast<int>(left.d) % static_cast<int>(right.d);
                return;
            case TokenType::CARET:
                checkNumberOperands(b->op, left, right);
                result.type = GenVal::Type::_double_;
                result.d = std::pow(left.d, right.d);
                return;
            case TokenType::PLUS:
                if(left.type == GenVal::Type::_double_ && right.type == GenVal::Type::_double_)
                {
                    result.type = GenVal::Type::_double_;
                    result.d = left.d + right.d;
                    return;
                }
                if(left.type == GenVal::Type::_string_ && right.type == GenVal::Type::_string_)
                {
                    result.type = GenVal::Type::_string_;
                    result.s = left.s + right.s;
                    return;
                }
                else
                    throw RunTimeError{b->op, "Operands must be two numbers or two strings."};
            // comparisons
            case TokenType::GREATER:
                checkNumberOperands(b->op, left, right);
                result.type = GenVal::Type::_bool_;
                result.b = left.d > right.d;
                return;
            case TokenType::GREATER_EQUAL:
                checkNumberOperands(b->op, left, right);
                result.type = GenVal::Type::_bool_;
                result.b = left.d >= right.d;
                return;
            case TokenType::LESS:
                checkNumberOperands(b->op, left, right);
                result.type = GenVal::Type::_bool_;
                result.b = left.d < right.d;
                return;
            case TokenType::LESS_EQUAL:
                checkNumberOperands(b->op, left, right);
                result.type = GenVal::Type::_bool_;
                result.b = left.d <= right.d;
                return;
            case TokenType::BANG_EQUAL:
                result.type = GenVal::Type::_bool_;
                result.b = !isEqual(left, right);
                return;
            case TokenType::EQUAL_EQUAL:
                result.type = GenVal::Type::_bool_;
                result.b = isEqual(left, right);
                return;
            default:
                break;
        }
        result.type = GenVal::Type::_null_;
    }

    void dispatch(Variable* v) override
    {
        GenVal value = environment.get(v->name);
        result.type = value.type;
        if(result.type == GenVal::Type::_bool_) 
            result.b = value.b;
        else if(result.type == GenVal::Type::_double_)
            result.d = value.d;
        else if(result.type == GenVal::Type::_string_)
            result.s = value.s;
    }

    // Stmt
    void dispatch(Expression* e) override
    {
        evaluate(e->expression);
    }

    void dispatch(Logical* l) override
    {
        GenVal left = evaluate(l->left);
        GenVal value = evaluate(l->right);

        if(l->op.type == TokenType::OR)
        {
            if(isTruthy(left)) 
            {
                if(left.type == GenVal::Type::_bool_)
                { 
                    result.type = GenVal::Type::_bool_;
                    result.b = left.b;
                }
                else if(left.type == GenVal::Type::_double_)
                {
                    result.type = GenVal::Type::_double_;
                    result.d = left.d;
                }
                else if(left.type == GenVal::Type::_string_)
                {
                    result.type = GenVal::Type::_string_;
                    result.s = left.s;
                }
            }
            return;
        }
        else
        {
            if(!isTruthy(left))
            {
                if(left.type == GenVal::Type::_bool_)
                { 
                    result.type = GenVal::Type::_bool_;
                    result.b = left.b;
                }
                else if(left.type == GenVal::Type::_double_)
                {
                    result.type = GenVal::Type::_double_;
                    result.d = left.d;
                }
                else if(left.type == GenVal::Type::_string_)
                {
                    result.type = GenVal::Type::_string_;
                    result.s = left.s;
                }
            }
            return;
        }

        
        if(value.type == GenVal::Type::_bool_)
        { 
            result.type = GenVal::Type::_bool_;
            result.b = value.b;
        }
        else if(value.type == GenVal::Type::_double_)
        {
            result.type = GenVal::Type::_double_;
            result.d = value.d;
        }
        else if(value.type == GenVal::Type::_string_)
        {
            result.type = GenVal::Type::_string_;
            result.s = value.s;
        }
    }

    void dispatch(If* i) override
    {
        if(isTruthy(evaluate(i->condition)))
        {
            execute(i->thenBranch);
        }
        else if (i->elseBranch != nullptr)
        {
            execute(i->elseBranch);
        }
    }

    void dispatch(Print* p) override
    {
        GenVal value = evaluate(p->expression);
        programOutput += value.toString() + "\n";
    }

    void dispatch(Var* v) override
    {
        if(v->initializer != nullptr)
        {
            environment.define(v->name.lexeme, evaluate(v->initializer));
        }
        else
        {
            environment.define(v->name.lexeme, GenVal{});
        }
    }

    void dispatch(While* w) override
    {
        while(isTruthy(evaluate(w->condition)))
        {
            execute(w->body);
        }
    }

    void dispatch(Assign* a) override
    {
        GenVal value = evaluate(a->value);
        environment.assign(a->name, value);

        result.type = value.type;
        if(result.type == GenVal::Type::_bool_) 
            result.b = value.b;
        else if(result.type == GenVal::Type::_double_)
            result.d = value.d;
        else if(result.type == GenVal::Type::_string_)
            result.s = value.s;
    }

    void dispatch(Block* b) override
    {
        executeBlock(b->statements);
    }
};
