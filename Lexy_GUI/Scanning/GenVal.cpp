#include "GenVal.hpp"
#include <ostream>

GenVal& GenVal::operator=(const GenVal& other)
{
    if(other.type == Type::_bool_)
    {
        type = Type::_bool_;
        b = other.b;
    }
    if(other.type == Type::_double_)
    {
        type = Type::_double_;
        d = other.d;
    }
    if(other.type == Type::_string_)
    {
        type = Type::_string_;
        s = other.s;
    }
    if(other.type == Type::_null_)
    {
        type = Type::_null_;
    }

    return *this;
}

std::ostream& operator<<(std::ostream& out, const GenVal& gv)
{
    out << "GenVal: (Type: " << utils::as_underlying(gv.type);
    if(gv.type == GenVal::Type::_double_) out << ", value: " << gv.d << ')';
    else if(gv.type == GenVal::Type::_string_) out << ", value: " << gv.s << ')';
    else if(gv.type == GenVal::Type::_bool_) out << ", value: " << std::boolalpha << gv.b << std::noboolalpha << ')';
    else if(gv.type == GenVal::Type::_null_) out << ", value: -- )";

    return out;
}

std::string GenVal::toString() const
{
    if(type == Type::_bool_ && b == false) return std::string{"false"};
    if(type == Type::_bool_ && b == true) return std::string {"true"};
    if(type == Type::_double_) return std::to_string(d);
    if(type == Type::_string_) return s;
    else return std::string{"?"};
}