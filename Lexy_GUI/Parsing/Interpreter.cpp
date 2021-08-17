#include "Interpreter.hpp"

GenVal Interpreter::evaluate(Expr* expr)
{
    expr->accept(this);
    return getResult();
}

void Interpreter::executeBlock(const std::vector<Stmt*>& statements)
{
    for(Stmt* statement : statements) execute(statement);
}

bool Interpreter::isTruthy(const GenVal& value)
{
    if(value.type == GenVal::Type::_bool_ && value.b == false) return false;
    if(value.type == GenVal::Type::_null_) return false;
    if(value.type == GenVal::Type::_double_ && value.d == 0.0) return false; 
    if(value.type == GenVal::Type::_string_ && value.s.length() == 0) return false;
    return true; // silence warnings
}

bool Interpreter::isEqual(const GenVal& lhs, const GenVal& rhs)
{
    if(lhs.type != rhs.type) return false;
    if(lhs.type == GenVal::Type::_bool_) return lhs.b == rhs.b;
    if(lhs.type == GenVal::Type::_double_) return lhs.d == rhs.d; // round-up? 
    if(lhs.type == GenVal::Type::_null_) return true;
    if(lhs.type == GenVal::Type::_string_) return lhs.s == rhs.s;
    return true; // silence warnings
}

void Interpreter::checkNumberOperand(const Token& op, const GenVal& operand)
{
    if(operand.type == GenVal::Type::_double_) return;
    throw RunTimeError{op, "Operand must be a number."};
}

void Interpreter::checkNumberOperands(const Token& op, const GenVal& lhs, const GenVal& rhs)
{
    if(lhs.type == GenVal::Type::_double_ && rhs.type == GenVal::Type::_double_) return;
    throw RunTimeError{op, "Operands must be numbers."};
}
