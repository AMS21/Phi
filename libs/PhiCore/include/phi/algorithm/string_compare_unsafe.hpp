#ifndef INCG_PHI_ALGORITHM_string_compare_unsafe_UNSAFE_HPP
#define INCG_PHI_ALGORITHM_string_compare_unsafe_UNSAFE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/extended_attributes.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/compiler_support/warning.hpp"
#include "phi/core/assert.hpp"
#include "phi/core/compare_result.hpp"
#include "phi/core/nullptr_t.hpp"
#include "phi/core/types.hpp"

PHI_CLANG_SUPPRESS_WARNING_PUSH()
PHI_CLANG_SUPPRESS_WARNING("-Wtautological-pointer-compare")
PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Wsuggest-attribute=pure")

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename CharT>
PHI_NODISCARD PHI_ATTRIBUTE_NONNULL PHI_EXTENDED_CONSTEXPR CompareResult
string_compare_unsafe(const CharT* lhs, const CharT* rhs) noexcept
{
    PHI_ASSERT(lhs != nullptr, "May not pass nullptr to string_compare_unsafe");
    PHI_ASSERT(rhs != nullptr, "May not pass nullptr to string_compare_unsafe");

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

template <typename CharT>
CompareResult string_compare_unsafe(const CharT*, nullptr_t) = delete;

template <typename CharT>
CompareResult string_compare_unsafe(nullptr_t, const CharT*) = delete;

template <typename CharT>
PHI_NODISCARD PHI_ATTRIBUTE_NONNULL_PARAMETERS(1, 2) PHI_EXTENDED_CONSTEXPR CompareResult
        string_compare_unsafe(const CharT* lhs, const CharT* rhs, usize count) noexcept
{
    PHI_ASSERT(lhs != nullptr, "May not pass nullptr to string_compare_unsafe");
    PHI_ASSERT(rhs != nullptr, "May not pass nullptr to string_compare_unsafe");

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

template <typename CharT>
CompareResult string_compare_unsafe(const CharT*, nullptr_t, usize) = delete;

template <typename CharT>
CompareResult string_compare_unsafe(nullptr_t, const CharT*, usize) = delete;

DETAIL_PHI_END_NAMESPACE()

PHI_GCC_SUPPRESS_WARNING_POP()
PHI_CLANG_SUPPRESS_WARNING_POP()

#endif // INCG_PHI_ALGORITHM_string_compare_unsafe_UNSAFE_HPP
