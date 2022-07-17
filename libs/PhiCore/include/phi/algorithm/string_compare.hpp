#ifndef INCG_PHI_CORE_ALGORITHM_STRING_COMPARE_HPP
#define INCG_PHI_CORE_ALGORITHM_STRING_COMPARE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/extended_attributes.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/compiler_support/unused.hpp"
#include "phi/compiler_support/warning.hpp"
#include "phi/core/assert.hpp"
#include "phi/core/sized_types.hpp"
#include "phi/core/types.hpp"
#include "phi/type_traits/make_signed.hpp"
#include <phi/core/nullptr_t.hpp>

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename CharT>
PHI_NODISCARD PHI_ATTRIBUTE_NONNULL PHI_EXTENDED_CONSTEXPR i32
string_compare(const CharT* lhs, const CharT* rhs) noexcept
{
    PHI_ASSERT(lhs != nullptr, "May not pass nullptr to string_compare");
    PHI_ASSERT(rhs != nullptr, "May not pass nullptr to string_compare");

    while (*lhs != CharT('\0') && (*lhs == *rhs))
    {
        ++lhs;
        ++rhs;
    }

    using SignedCharT = typename make_signed<CharT>::type;

    return static_cast<phi::int32_t>(*static_cast<SignedCharT>(lhs) -
                                     *static_cast<SignedCharT>(rhs));
}

template <typename CharT>
i32 string_compare(const CharT*, nullptr_t) = delete;

template <typename CharT>
i32 string_compare(nullptr_t, const CharT*) = delete;

template <typename CharT>
PHI_NODISCARD PHI_ATTRIBUTE_NONNULL PHI_EXTENDED_CONSTEXPR i32 string_compare(const CharT* lhs,
                                                                              const CharT* rhs,
                                                                              usize count) noexcept
{
    PHI_ASSERT(lhs != nullptr, "May not pass nullptr to string_compare");
    PHI_ASSERT(rhs != nullptr, "May not pass nullptr to string_compare");

    while (*lhs != CharT('\0') && (*lhs == *rhs) && (count-- > 0u))
    {
        ++lhs;
        ++rhs;
    }

    using SignedCharT = typename make_signed<CharT>::type;

    return static_cast<phi::int32_t>(*static_cast<SignedCharT>(lhs) -
                                     *static_cast<SignedCharT>(rhs));
}

template <typename CharT>
i32 string_compare(const CharT*, nullptr_t, usize) = delete;

template <typename CharT>
i32 string_compare(nullptr_t, const CharT*, usize) = delete;

template <typename CharT>
PHI_NODISCARD PHI_EXTENDED_CONSTEXPR i32 safe_string_compare(const CharT* lhs,
                                                             const CharT* rhs) noexcept
{
    if (lhs == nullptr)
    {
        if (rhs == nullptr)
        {
            return 0;
        }

        return -1;
    }
    if (rhs == nullptr)
    {
        return 1;
    }

    while (*lhs != CharT('\0') && (*lhs == *rhs))
    {
        ++lhs;
        ++rhs;
    }

    using SignedCharT = typename make_signed<CharT>::type;

    return static_cast<phi::int32_t>(*static_cast<SignedCharT>(lhs) -
                                     *static_cast<SignedCharT>(rhs));
}

template <typename CharT>
PHI_NODISCARD constexpr i32 safe_string_compare(const CharT* lhs, nullptr_t) noexcept
{
#if PHI_HAS_FEATURE_EXTENDED_CONSTEXPR()
    if (lhs == nullptr)
    {
        return 0;
    }

    return -1;
#else
    return lhs == nullptr ? 0 : -1;
#endif
}

template <typename CharT>
PHI_NODISCARD constexpr i32 safe_string_compare(nullptr_t, const CharT* rhs) noexcept
{
#if PHI_HAS_FEATURE_EXTENDED_CONSTEXPR()
    if (rhs == nullptr)
    {
        return 0;
    }

    return 1;
#else
    return rhs == nullptr ? 0 : 1;
#endif
}

template <typename CharT>
PHI_NODISCARD PHI_EXTENDED_CONSTEXPR i32 safe_string_compare(const CharT* lhs, const CharT* rhs,
                                                             usize count) noexcept
{
    if (lhs == nullptr)
    {
        if (rhs == nullptr)
        {
            return 0;
        }
        return -1;
    }
    if (rhs == nullptr)
    {
        return 1;
    }

    while (*lhs != CharT('\0') && (*lhs == *rhs) && (count-- > 0u))
    {
        ++lhs;
        ++rhs;
    }

    using SignedCharT = typename make_signed<CharT>::type;

    return static_cast<phi::int32_t>(*static_cast<SignedCharT>(lhs) -
                                     *static_cast<SignedCharT>(rhs));
}

template <typename CharT>
PHI_NODISCARD constexpr i32 safe_string_compare(const CharT*     lhs, nullptr_t,
                                                PHI_UNUSED usize size) noexcept
{
#if PHI_HAS_FEATURE_EXTENDED_CONSTEXPR()
    if (lhs == nullptr)
    {
        return 0;
    }

    return -1;
#else
    return lhs == nullptr ? 0 : -1;
#endif
}

template <typename CharT>
PHI_NODISCARD constexpr i32 safe_string_compare(nullptr_t, const CharT* rhs,
                                                PHI_UNUSED usize size) noexcept
{
#if PHI_HAS_FEATURE_EXTENDED_CONSTEXPR()
    if (rhs == nullptr)
    {
        return 0;
    }

    return 1;
#else
    return rhs == nullptr ? 0 : 1;
#endif
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_ALGORITHM_STRING_COMPARE_HPP
