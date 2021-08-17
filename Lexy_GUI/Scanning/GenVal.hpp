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
    GenVal(double d) : d{d}, type{Type::_double_} {}
    GenVal(const std::string& s) : s{s}, type{Type::_string_} {}
    GenVal(bool b) : b{b}, type{Type::_bool_} {}
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