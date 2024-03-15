#ifndef INCG_PHI_ALGORITHM_STRING_LENGTH_UNSAFE_HPP
#define INCG_PHI_ALGORITHM_STRING_LENGTH_UNSAFE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/algorithm/min.hpp"
#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/compiler_support/noexcept.hpp"
#include "phi/core/assert.hpp"
#include "phi/core/nullptr_t.hpp"
#include "phi/core/types.hpp"
#include "phi/forward/std/string.hpp"
#include "phi/forward/std/string_view.hpp"
#include "phi/forward/string_view.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename CharT>
PHI_NODISCARD PHI_ATTRIBUTE_NONNULL PHI_EXTENDED_CONSTEXPR usize string_length_unsafe(CharT* string)
        PHI_NOEXCEPT
{
    PHI_ASSERT(string != nullptr, "Passing nullptr to string_length_unsafe is not allowed. Use "
                                  "string_length if you intended to pass a nullptr.");

    usize count = 0u;
    for (; *string != CharT('\0'); ++string)
    {
        ++count;
    }

    return count;
}

template <typename CharT, typename TraitsT>
PHI_NODISCARD PHI_CONSTEXPR usize string_length_unsafe(basic_string_view<CharT, TraitsT> string)
        PHI_NOEXCEPT
{
    return string.length();
}

template <typename CharT, typename TraitsT, typename AllocatorT>
PHI_NODISCARD PHI_CONSTEXPR usize
string_length_unsafe(std::basic_string<CharT, TraitsT, AllocatorT> string) PHI_NOEXCEPT
{
    return string.length();
}

template <typename CharT, typename TraitsT>
PHI_NODISCARD PHI_CONSTEXPR usize
string_length_unsafe(std::basic_string_view<CharT, TraitsT> string) PHI_NOEXCEPT
{
    return string.length();
}

template <typename CharT = nullptr_t>
PHI_NODISCARD PHI_CONSTEXPR usize string_length_unsafe(nullptr_t) PHI_NOEXCEPT = delete;

template <typename CharT>
PHI_NODISCARD PHI_ATTRIBUTE_NONNULL PHI_EXTENDED_CONSTEXPR usize
string_length_unsafe(CharT* string, usize length) PHI_NOEXCEPT
{
    PHI_ASSERT(string != nullptr, "Passing nullptr to string_length_unsafe is not allowed. Use "
                                  "string_length if you intended to pass a nullptr.");

    usize count = 0u;
    for (; count < length && *string != CharT('\0'); ++string)
    {
        ++count;
    }

    return count;
}

template <typename CharT, typename TraitsT>
PHI_NODISCARD PHI_CONSTEXPR usize string_length_unsafe(basic_string_view<CharT, TraitsT> string,
                                                       usize length) PHI_NOEXCEPT
{
    return min(usize(string.length()), length);
}

template <typename CharT, typename TraitsT, typename AllocatorT>
PHI_NODISCARD PHI_CONSTEXPR usize string_length_unsafe(
        std::basic_string<CharT, TraitsT, AllocatorT> string, usize length) PHI_NOEXCEPT
{
    return min(usize(string.length()), length);
}

template <typename CharT, typename TraitsT>
PHI_NODISCARD PHI_CONSTEXPR usize
string_length_unsafe(std::basic_string_view<CharT, TraitsT> string, usize length) PHI_NOEXCEPT
{
    return min(usize(string.length()), length);
}

template <typename CharT = nullptr_t>
PHI_NODISCARD PHI_CONSTEXPR usize string_length_unsafe(nullptr_t, usize) PHI_NOEXCEPT = delete;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_ALGORITHM_STRING_LENGTH_UNSAFE_HPP
