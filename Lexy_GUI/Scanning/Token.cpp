#include "Token.hpp"
#include <ostream>

std::ostream& operator<<(std::ostream& out, const Token& t)
{
    out << "TokenType: " << utils::as_underlying(t.type) << ", lexeme: " << t.lexeme;
    out << ", literal: " << t.literal << ", line: " << t.line;
    return out;
}