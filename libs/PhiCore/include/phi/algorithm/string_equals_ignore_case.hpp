#ifndef INCG_PHI_CORE_ALGORITHM_STRING_EQUALS_IGNORE_CASE_HPP
#define INCG_PHI_CORE_ALGORITHM_STRING_EQUALS_IGNORE_CASE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/nodiscard.hpp"
#include "phi/core/boolean.hpp"
#include "phi/core/nullptr_t.hpp"
#include "phi/forward/std/string.hpp"
#include "phi/forward/std/string_view.hpp"
#include "phi/forward/string_view.hpp"
#include "phi/text/to_lower_case.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

// nullptr_t - x

template <typename CharT = char>
PHI_NODISCARD constexpr boolean string_equals_ignore_case(nullptr_t, nullptr_t) noexcept
{
    return true;
}

template <typename CharT>
PHI_NODISCARD constexpr boolean string_equals_ignore_case(nullptr_t, const CharT* rhs) noexcept
{
    return rhs == nullptr;
}

template <typename CharT, typename TraitsT>
PHI_NODISCARD constexpr boolean string_equals_ignore_case(
        nullptr_t, basic_string_view<CharT, TraitsT> rhs) noexcept
{
    return rhs.is_null();
}

template <typename CharT, typename TraitsT>
PHI_NODISCARD constexpr boolean string_equals_ignore_case(
        nullptr_t, std::basic_string_view<CharT, TraitsT> rhs) noexcept
{
    return rhs.data() == nullptr;
}

template <typename CharT, typename TraitsT, typename AllocatorT>
PHI_NODISCARD constexpr boolean string_equals_ignore_case(
        nullptr_t, std::basic_string<CharT, TraitsT, AllocatorT> rhs) noexcept
{
    return rhs.data() == nullptr;
}

// CharT - x

template <typename CharT>
PHI_NODISCARD constexpr boolean string_equals_ignore_case(const CharT* lhs, nullptr_t) noexcept
{
    return lhs == nullptr;
}

template <typename CharT>
PHI_NODISCARD PHI_EXTENDED_CONSTEXPR boolean string_equals_ignore_case(const CharT* lhs,
                                                                       const CharT* rhs) noexcept
{
    if ((lhs == nullptr || rhs == nullptr))
    {
        return static_cast<bool>(lhs == rhs);
    }

    while (*lhs != CharT('\0'))
    {
        if (to_lower_case(*lhs) != to_lower_case(*rhs))
        {
            return false;
        }

        ++lhs;
        ++rhs;
    }

    return to_lower_case(*lhs) == to_lower_case(*rhs);
}

template <typename CharT, typename TraitsT>
PHI_NODISCARD PHI_EXTENDED_CONSTEXPR boolean
string_equals_ignore_case(const CharT* lhs, basic_string_view<CharT, TraitsT> rhs) noexcept
{
    return string_equals_ignore_case(lhs, rhs.data());
}

template <typename CharT, typename TraitsT>
PHI_NODISCARD PHI_EXTENDED_CONSTEXPR boolean
string_equals_ignore_case(const CharT* lhs, std::basic_string_view<CharT, TraitsT> rhs) noexcept
{
    return string_equals_ignore_case(lhs, rhs.data());
}

template <typename CharT, typename TraitsT, typename AllocatorT>
PHI_NODISCARD constexpr boolean string_equals_ignore_case(
        const CharT* lhs, std::basic_string<CharT, TraitsT, AllocatorT> rhs) noexcept
{
    return string_equals_ignore_case(lhs, rhs.data());
}

// phi::basic_string_view - x

template <typename CharT, typename TraitsT>
PHI_NODISCARD constexpr boolean string_equals_ignore_case(basic_string_view<CharT, TraitsT> lhs,
                                                          nullptr_t) noexcept
{
    return lhs.is_null();
}

template <typename CharT, typename TraitsT>
PHI_NODISCARD PHI_EXTENDED_CONSTEXPR boolean
string_equals_ignore_case(basic_string_view<CharT, TraitsT> lhs, const CharT* rhs) noexcept
{
    return string_equals_ignore_case(lhs.data(), rhs);
}

template <typename CharT, typename TraitsT>
PHI_NODISCARD constexpr boolean string_equals_ignore_case(
        basic_string_view<CharT, TraitsT> lhs, basic_string_view<CharT, TraitsT> rhs) noexcept
{
    return string_equals_ignore_case(lhs.data(), rhs.data());
}

template <typename CharT, typename TraitsT>
PHI_NODISCARD constexpr boolean string_equals_ignore_case(
        basic_string_view<CharT, TraitsT> lhs, std::basic_string_view<CharT, TraitsT> rhs) noexcept
{
    return string_equals_ignore_case(lhs.data(), rhs.data());
}

template <typename CharT, typename TraitsT, typename AllocatorT>
PHI_NODISCARD constexpr boolean string_equals_ignore_case(
        basic_string_view<CharT, TraitsT>             lhs,
        std::basic_string<CharT, TraitsT, AllocatorT> rhs) noexcept
{
    return string_equals_ignore_case(lhs.data(), rhs.data());
}

// std::string_view - x

template <typename CharT, typename TraitsT>
PHI_NODISCARD constexpr boolean string_equals_ignore_case(
        std::basic_string_view<CharT, TraitsT> lhs, nullptr_t) noexcept
{
    return lhs.data() == nullptr;
}

template <typename CharT, typename TraitsT>
PHI_NODISCARD PHI_EXTENDED_CONSTEXPR boolean
string_equals_ignore_case(std::basic_string_view<CharT, TraitsT> lhs, const CharT* rhs) noexcept
{
    return string_equals_ignore_case(lhs.data(), rhs);
}

template <typename CharT, typename TraitsT>
PHI_NODISCARD constexpr boolean string_equals_ignore_case(
        std::basic_string_view<CharT, TraitsT> lhs, basic_string_view<CharT, TraitsT> rhs) noexcept
{
    return string_equals_ignore_case(lhs.data(), rhs.data());
}

template <typename CharT, typename TraitsT>
PHI_NODISCARD constexpr boolean string_equals_ignore_case(
        std::basic_string_view<CharT, TraitsT> lhs,
        std::basic_string_view<CharT, TraitsT> rhs) noexcept
{
    return string_equals_ignore_case(lhs.data(), rhs.data());
}

template <typename CharT, typename TraitsT, typename AllocatorT>
PHI_NODISCARD constexpr boolean string_equals_ignore_case(
        std::basic_string_view<CharT, TraitsT>        lhs,
        std::basic_string<CharT, TraitsT, AllocatorT> rhs) noexcept
{
    return string_equals_ignore_case(lhs.data(), rhs.data());
}

// std::basic_string - x

template <typename CharT, typename TraitsT, typename AllocatorT>
PHI_NODISCARD constexpr boolean string_equals_ignore_case(
        std::basic_string<CharT, TraitsT, AllocatorT> lhs, nullptr_t) noexcept
{
    return lhs.data() == nullptr;
}

template <typename CharT, typename TraitsT, typename AllocatorT>
PHI_NODISCARD constexpr boolean string_equals_ignore_case(
        std::basic_string<CharT, TraitsT, AllocatorT> lhs, const CharT* rhs) noexcept
{
    return string_equals_ignore_case(lhs.data(), rhs);
}

template <typename CharT, typename TraitsT, typename AllocatorT>
PHI_NODISCARD constexpr boolean string_equals_ignore_case(
        std::basic_string<CharT, TraitsT, AllocatorT> lhs,
        basic_string_view<CharT, TraitsT>             rhs) noexcept
{
    return string_equals_ignore_case(lhs.data(), rhs.data());
}

template <typename CharT, typename TraitsT, typename AllocatorT>
PHI_NODISCARD constexpr boolean string_equals_ignore_case(
        std::basic_string<CharT, TraitsT, AllocatorT> lhs,
        std::basic_string_view<CharT, TraitsT>        rhs) noexcept
{
    return string_equals_ignore_case(lhs.data(), rhs.data());
}

template <typename CharT, typename TraitsT, typename AllocatorT>
PHI_NODISCARD constexpr boolean string_equals_ignore_case(
        std::basic_string<CharT, TraitsT, AllocatorT> lhs,
        std::basic_string<CharT, TraitsT, AllocatorT> rhs) noexcept
{
    return string_equals_ignore_case(lhs.data(), rhs.data());
}

DETAIL_PHI_END_NAMESPACE()

#endif
