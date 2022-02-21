#ifndef INCG_PHI_CORE_ALGORITHM_STRING_EQUALS_HPP
#define INCG_PHI_CORE_ALGORITHM_STRING_EQUALS_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/core/boolean.hpp"
#include "phi/core/nullptr_t.hpp"
#include "phi/core/types.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename CharT>
PHI_NODISCARD PHI_EXTENDED_CONSTEXPR boolean string_equals(const CharT* lhs,
                                                           const CharT* rhs) noexcept
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
PHI_NODISCARD PHI_EXTENDED_CONSTEXPR boolean string_equals(const CharT* lhs, const CharT* rhs,
                                                           usize count) noexcept
{
    if ((lhs == nullptr || rhs == nullptr))
    {
        return static_cast<bool>(lhs == rhs);
    }

    while (*lhs != CharT('\0') && (--count > 0u))
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
PHI_NODISCARD constexpr boolean string_equals(const CharT* lhs, nullptr_t) noexcept
{
    return lhs == nullptr;
}

template <typename CharT>
PHI_NODISCARD constexpr boolean string_equals(nullptr_t, const CharT* rhs) noexcept
{
    return rhs == nullptr;
}

template <typename CharT>
PHI_NODISCARD constexpr boolean string_equals(nullptr_t, nullptr_t) noexcept
{
    return true;
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_ALGORITHM_STRING_EQUALS_HPP
