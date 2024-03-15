#ifndef INCG_PHI_CORE_ALGORITHM_STRING_COMPARE_HPP
#define INCG_PHI_CORE_ALGORITHM_STRING_COMPARE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/compiler_support/unused.hpp"
#include "phi/core/compare_result.hpp"
#include "phi/core/nullptr_t.hpp"
#include "phi/core/types.hpp"
#include "phi/type_traits/make_signed.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename CharT>
PHI_NODISCARD PHI_EXTENDED_CONSTEXPR CompareResult string_compare(const CharT* lhs,
                                                                  const CharT* rhs) noexcept
{
    if (lhs == nullptr)
    {
        if (rhs == nullptr)
        {
            return CompareResult::Equal;
        }

        return CompareResult::LessThan;
    }
    if (rhs == nullptr)
    {
        return CompareResult::GreaterThan;
    }

    while (*lhs != CharT('\0') && (*lhs == *rhs))
    {
        ++lhs;
        ++rhs;
    }

    using SignedCharT = typename make_signed<CharT>::type;

    const phi::int32_t diff = static_cast<phi::int32_t>(static_cast<SignedCharT>(*lhs) -
                                                        static_cast<SignedCharT>(*rhs));

    if (diff == 0)
    {
        return CompareResult::Equal;
    }
    if (diff < 0)
    {
        return CompareResult::LessThan;
    }

    return CompareResult::GreaterThan;
}

PHI_NODISCARD PHI_CONSTEXPR CompareResult string_compare(nullptr_t, nullptr_t) noexcept
{
    return CompareResult::Equal;
}

template <typename CharT>
PHI_NODISCARD PHI_CONSTEXPR CompareResult string_compare(const CharT* lhs, nullptr_t) noexcept
{
    return lhs == nullptr ? CompareResult::Equal : CompareResult::GreaterThan;
}

template <typename CharT>
PHI_NODISCARD PHI_CONSTEXPR CompareResult string_compare(nullptr_t, const CharT* rhs) noexcept
{
    return rhs == nullptr ? CompareResult::Equal : CompareResult::LessThan;
}

template <typename CharT>
PHI_NODISCARD PHI_EXTENDED_CONSTEXPR CompareResult string_compare(const CharT* lhs,
                                                                  const CharT* rhs,
                                                                  usize        count) noexcept
{
    if (lhs == nullptr)
    {
        if (rhs == nullptr)
        {
            return CompareResult::Equal;
        }
        return CompareResult::LessThan;
    }
    if (rhs == nullptr)
    {
        return CompareResult::GreaterThan;
    }

    while (*lhs != CharT('\0') && (*lhs == *rhs) && (count > 0u))
    {
        ++lhs;
        ++rhs;
        --count;
    }

    using SignedCharT = typename make_signed<CharT>::type;

    const phi::int32_t diff = static_cast<phi::int32_t>(static_cast<SignedCharT>(*lhs) -
                                                        static_cast<SignedCharT>(*rhs));

    if (diff == 0)
    {
        return CompareResult::Equal;
    }
    if (diff < 0)
    {
        return CompareResult::LessThan;
    }

    return CompareResult::GreaterThan;
}

PHI_NODISCARD PHI_CONSTEXPR CompareResult string_compare(nullptr_t, nullptr_t,
                                                         PHI_UNUSED usize size) noexcept
{
    return CompareResult::Equal;
}

template <typename CharT>
PHI_NODISCARD PHI_CONSTEXPR CompareResult string_compare(const CharT*     lhs, nullptr_t,
                                                         PHI_UNUSED usize size) noexcept
{
    return lhs == nullptr ? CompareResult::Equal : CompareResult::GreaterThan;
}

template <typename CharT>
PHI_NODISCARD PHI_CONSTEXPR CompareResult string_compare(nullptr_t, const CharT* rhs,
                                                         PHI_UNUSED usize size) noexcept
{
    return rhs == nullptr ? CompareResult::Equal : CompareResult::LessThan;
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_ALGORITHM_STRING_COMPARE_HPP
