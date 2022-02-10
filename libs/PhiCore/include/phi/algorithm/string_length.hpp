#ifndef INCG_PHI_CORE_ALGORITHM_STRING_LENGTH_HPP
#define INCG_PHI_CORE_ALGORITHM_STRING_LENGTH_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/algorithm/min.hpp"
#include "phi/compiler_support/compiler.hpp"
#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/cpp_standard.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/compiler_support/unused.hpp"
#include "phi/compiler_support/warning.hpp"
#include "phi/core/assert.hpp"
#include "phi/core/nullptr_t.hpp"
#include "phi/core/types.hpp"
#include "phi/math/common.hpp"
#include <string>

#if PHI_HAS_LIB_STRING_VIEW()
#    include <string_view>
#endif

PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Winline")

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename CharT>
PHI_NODISCARD PHI_EXTENDED_CONSTEXPR usize string_length(CharT* string) noexcept
{
    PHI_DBG_ASSERT(string != nullptr, "Passing nullptr to string_length is not allowed. Use "
                                      "safe_string_length if you intended to pass a nullptr.");

    usize count = 0u;
    for (; *string != CharT('\0'); ++string)
    {
        ++count;
    }

    return count;
}

template <typename CharT, typename TraitsT, typename AllocatorT>
PHI_NODISCARD constexpr usize string_length(
        std::basic_string<CharT, TraitsT, AllocatorT> string) noexcept
{
    return string.length();
}

#if PHI_HAS_LIB_STRING_VIEW()
template <typename CharT, typename TraitsT>
PHI_NODISCARD constexpr usize string_length(std::basic_string_view<CharT, TraitsT> string) noexcept
{
    return string.length();
}
#endif

template <typename CharT = nullptr_t>
PHI_NODISCARD constexpr usize string_length(nullptr_t) noexcept = delete;

template <typename CharT>
PHI_NODISCARD PHI_EXTENDED_CONSTEXPR usize string_length(CharT* string, usize length) noexcept
{
    PHI_DBG_ASSERT(string != nullptr, "Passing nullptr to string_length is not allowed. Use "
                                      "safe_string_length if you intended to pass a nullptr.");

    usize count = 0u;
    for (; count < length && *string != CharT('\0'); ++string)
    {
        ++count;
    }

    return count;
}

template <typename CharT, typename TraitsT, typename AllocatorT>
PHI_NODISCARD constexpr usize string_length(std::basic_string<CharT, TraitsT, AllocatorT> string,
                                            usize length) noexcept
{
    return min(usize(string.length()), length);
}

#if PHI_HAS_LIB_STRING_VIEW()
template <typename CharT, typename TraitsT>
PHI_NODISCARD constexpr usize string_length(std::basic_string_view<CharT, TraitsT> string,
                                            usize                                  length) noexcept
{
    return min(usize(string.length()), length);
}
#endif

template <typename CharT = nullptr_t>
PHI_NODISCARD constexpr usize string_length(nullptr_t, usize) noexcept = delete;

template <typename CharT>
PHI_NODISCARD PHI_EXTENDED_CONSTEXPR usize safe_string_length(CharT* string) noexcept
{
    if (string == nullptr)
    {
        return 0u;
    }

    usize count = 0u;
    for (; *string != CharT('\0'); ++string)
    {
        ++count;
    }

    return count;
}

template <typename CharT, typename TraitsT, typename AllocatorT>
PHI_NODISCARD constexpr usize safe_string_length(
        std::basic_string<CharT, TraitsT, AllocatorT> string) noexcept
{
    return string.length();
}

#if PHI_HAS_LIB_STRING_VIEW()
template <typename CharT, typename TraitsT>
PHI_NODISCARD constexpr usize safe_string_length(
        std::basic_string_view<CharT, TraitsT> string) noexcept
{
    return string.length();
}
#endif

template <typename CharT = nullptr_t>
PHI_NODISCARD constexpr usize safe_string_length(nullptr_t) noexcept
{
    return 0u;
}

template <typename CharT>
PHI_NODISCARD PHI_EXTENDED_CONSTEXPR usize safe_string_length(CharT* string, usize length) noexcept
{
    if (string == nullptr)
    {
        return 0u;
    }

    usize count = 0u;
    for (; count < length && *string != CharT('\0'); ++string)
    {
        ++count;
    }

    return count;
}

template <typename CharT, typename TraitsT, typename AllocatorT>
PHI_NODISCARD constexpr usize safe_string_length(
        std::basic_string<CharT, TraitsT, AllocatorT> string, usize length) noexcept
{
    return min(usize(string.length()), length);
}

#if PHI_HAS_LIB_STRING_VIEW()
template <typename CharT, typename TraitsT>
PHI_NODISCARD constexpr usize safe_string_length(std::basic_string_view<CharT, TraitsT> string,
                                                 usize length) noexcept
{
    return min(usize(string.length()), length);
}
#endif

template <typename CharT = nullptr_t>
PHI_NODISCARD constexpr usize safe_string_length(nullptr_t, PHI_UNUSED usize length) noexcept
{
    return 0u;
}

DETAIL_PHI_END_NAMESPACE()

PHI_GCC_SUPPRESS_WARNING_POP()

#endif // INCG_PHI_CORE_ALGORITHM_STRING_LENGTH_HPP
