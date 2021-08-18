#pragma once
#include <string>
#include <ostream>
#include "generalUtilities.hpp"

class GenVal
{
public:
    enum class Type
    {
        _double_, _string_, _bool_, _null_
    };
    GenVal(double d) : type{Type::_double_}, d{d} {}
    GenVal(const std::string& s) : type{Type::_string_}, s{s} {}
    GenVal(bool b) : type{Type::_bool_}, b{b} {}
    GenVal(std::nullptr_t) : type{Type::_null_} {}
    GenVal() : GenVal(nullptr) {} // default constructor
    GenVal& operator=(const GenVal& other);
    Type type = Type::_null_;
    double d = 0;
    std::string s = "";
    bool b = false;
    friend std::ostream& operator<<(std::ostream& out, const GenVal& gv);
    std::string toString() const;
};
