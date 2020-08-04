#pragma once

#include <cstddef>

template <typename CharT>
[[nodiscard]] constexpr std::size_t string_length(const CharT* str) noexcept
{
    if (str == nullptr)
    {
        return 0;
    }

    std::size_t length{0};
    while (*str != '\0')
    {
        ++length;
        ++str;
    }

    return length;
}

template <typename CharT>
[[nodiscard]] constexpr bool string_equals(const CharT* lhs, const CharT* rhs) noexcept
{
    if ((lhs == nullptr || rhs == nullptr))
    {
        if (lhs == rhs)
        {
            return true;
        }

        return false;
    }

    while (*lhs != '\0')
    {
        if (*lhs != *rhs)
        {
            return false;
        }

        ++lhs;
        ++rhs;
    }

    return *lhs == *rhs;
}
