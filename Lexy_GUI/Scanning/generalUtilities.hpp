#pragma once
#include <type_traits>

namespace utils
{
    template<typename T>
    auto as_underlying(T value) -> typename std::underlying_type<T>::type
    {
        return static_cast<typename std::underlying_type<T>::type>(value);
    }

    bool isDigit(char c) noexcept;
    bool isAlpha(char c) noexcept;
    bool isAlphaNumeric(char c) noexcept;
}