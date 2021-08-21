#ifndef INCG_PHI_CORE_ALGORITHM_STRING_EQUALS_HPP
#define INCG_PHI_CORE_ALGORITHM_STRING_EQUALS_HPP

#include "Phi/Core/Boolean.hpp"
#include "Phi/Core/Types.hpp"
#include "Phi/PhiConfig.hpp"
#include <cstddef>
#include <functional>
#include <utility>

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename CharT>
[[nodiscard]] constexpr Boolean StringEquals(const CharT* lhs, const CharT* rhs) noexcept
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

template <typename CharT>
[[nodiscard]] constexpr Boolean StringEquals(const CharT* lhs, const CharT* rhs,
                                             usize count) noexcept
{
    if ((lhs == nullptr || rhs == nullptr))
    {
        return static_cast<bool>(lhs == rhs);
    }

    while (*lhs != CharT('\0') && (count-- > 0u))
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

template <typename CharT>
[[nodiscard]] constexpr Boolean StringEquals(const CharT* lhs, std::nullptr_t) noexcept
{
    return lhs == nullptr;
}

template <typename CharT>
[[nodiscard]] constexpr Boolean StringEquals(std::nullptr_t, const CharT* rhs) noexcept
{
    return rhs == nullptr;
}

template <typename CharT>
[[nodiscard]] constexpr Boolean StringEquals(std::nullptr_t, std::nullptr_t) noexcept
{
    return true;
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_ALGORITHM_STRING_EQUALS_HPP
