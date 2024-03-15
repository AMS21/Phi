#ifndef INCG_PHI_CORE_ALGORITHM_STRING_LENGTH_HPP
#define INCG_PHI_CORE_ALGORITHM_STRING_LENGTH_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/algorithm/min.hpp"
#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/compiler_support/unused.hpp"
#include "phi/core/nullptr_t.hpp"
#include "phi/core/types.hpp"
#include "phi/forward/std/string.hpp"
#include "phi/forward/std/string_view.hpp"
#include "phi/forward/string_view.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename CharT>
PHI_NODISCARD PHI_EXTENDED_CONSTEXPR usize string_length(CharT* string) noexcept
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

template <typename CharT, typename TraitsT>
PHI_NODISCARD PHI_CONSTEXPR usize string_length(basic_string_view<CharT, TraitsT> string) noexcept
{
    return string.length();
}

template <typename CharT, typename TraitsT, typename AllocatorT>
PHI_NODISCARD PHI_CONSTEXPR usize
string_length(std::basic_string<CharT, TraitsT, AllocatorT> string) noexcept
{
    return string.length();
}

template <typename CharT, typename TraitsT>
PHI_NODISCARD PHI_CONSTEXPR usize
string_length(std::basic_string_view<CharT, TraitsT> string) noexcept
{
    return string.length();
}

template <typename CharT = nullptr_t>
PHI_NODISCARD PHI_CONSTEXPR usize string_length(nullptr_t) noexcept
{
    return 0u;
}

template <typename CharT>
PHI_NODISCARD PHI_EXTENDED_CONSTEXPR usize string_length(CharT* string, usize length) noexcept
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

template <typename CharT, typename TraitsT>
PHI_NODISCARD PHI_CONSTEXPR usize string_length(basic_string_view<CharT, TraitsT> string,
                                                usize                             length) noexcept
{
    return min(string.length(), length);
}

template <typename CharT, typename TraitsT, typename AllocatorT>
PHI_NODISCARD PHI_CONSTEXPR usize
string_length(std::basic_string<CharT, TraitsT, AllocatorT> string, usize length) noexcept
{
    return min(usize(string.length()), length);
}

template <typename CharT, typename TraitsT>
PHI_NODISCARD PHI_CONSTEXPR usize string_length(std::basic_string_view<CharT, TraitsT> string,
                                                usize length) noexcept
{
    return min(usize(string.length()), length);
}

template <typename CharT = nullptr_t>
PHI_NODISCARD PHI_CONSTEXPR usize string_length(nullptr_t, PHI_UNUSED usize length) noexcept
{
    return 0u;
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_ALGORITHM_STRING_LENGTH_HPP
