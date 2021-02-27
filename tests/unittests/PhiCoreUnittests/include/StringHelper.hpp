#ifndef INCG_PHI_UNITTEST_STRINGHELPER_HPP
#define INCG_PHI_UNITTEST_STRINGHELPER_HPP

#include <cstddef>

template <typename CharT>
[[nodiscard]] constexpr std::size_t string_length(const CharT* str) noexcept
{
    if (str == nullptr)
    {
        return 0;
    }

    std::size_t length{0};
    while (*str != CharT('\0'))
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
        return static_cast<bool>(lhs == rhs);
    }

    while (*lhs != CharT('\0'))
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

#endif // INCG_PHI_UNITTEST_STRINGHELPER_HPP
