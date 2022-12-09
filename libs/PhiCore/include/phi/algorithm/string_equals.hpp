#ifndef INCG_PHI_CORE_ALGORITHM_STRING_EQUALS_HPP
#define INCG_PHI_CORE_ALGORITHM_STRING_EQUALS_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/compiler_support/standard_library.hpp"
#include "phi/core/boolean.hpp"
#include "phi/core/nullptr_t.hpp"
#include "phi/core/types.hpp"

// Forward declarations
DETAIL_PHI_BEGIN_STD_NAMESPACE()

template <typename CharT, typename TraitsT>
class basic_string_view;

#if PHI_STANDARD_LIBRARY_LIBSTDCXX()
inline namespace __cxx11
{
#endif

    template <typename CharT, typename TraitsT, typename AllocatorT>
    class basic_string;

#if PHI_STANDARD_LIBRARY_LIBSTDCXX()
}
#endif

template <typename CharT, typename TraitsT>
class basic_string_view;

DETAIL_PHI_END_STD_NAMESPACE()

DETAIL_PHI_BEGIN_NAMESPACE()

// Forward declaration
template <typename CharT, typename TraitsT>
class basic_string_view;

// nullptr_t - x

template <typename CharT = char>
PHI_NODISCARD constexpr boolean string_equals(nullptr_t, nullptr_t) noexcept
{
    return true;
}

template <typename CharT>
PHI_NODISCARD constexpr boolean string_equals(nullptr_t, const CharT* rhs) noexcept
{
    return rhs == nullptr;
}

template <typename CharT, typename TraitsT>
PHI_NODISCARD constexpr boolean string_equals(nullptr_t,
                                              basic_string_view<CharT, TraitsT> rhs) noexcept
{
    return rhs.is_null();
}

template <typename CharT, typename TraitsT>
PHI_NODISCARD constexpr boolean string_equals(nullptr_t,
                                              std::basic_string_view<CharT, TraitsT> rhs) noexcept
{
    return rhs.data() == nullptr;
}

template <typename CharT, typename TraitsT, typename AllocatorT>
PHI_NODISCARD constexpr boolean string_equals(
        nullptr_t, std::basic_string<CharT, TraitsT, AllocatorT> rhs) noexcept
{
    return rhs.data() == nullptr;
}

// CharT - x

template <typename CharT>
PHI_NODISCARD constexpr boolean string_equals(const CharT* lhs, nullptr_t) noexcept
{
    return lhs == nullptr;
}

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

template <typename CharT, typename TraitsT>
PHI_NODISCARD PHI_EXTENDED_CONSTEXPR boolean
string_equals(const CharT* lhs, basic_string_view<CharT, TraitsT> rhs) noexcept
{
    if (lhs == nullptr)
    {
        return rhs.is_null();
    }

    return lhs == rhs;
}

template <typename CharT, typename TraitsT>
PHI_NODISCARD PHI_EXTENDED_CONSTEXPR boolean
string_equals(const CharT* lhs, std::basic_string_view<CharT, TraitsT> rhs) noexcept
{
    // Check for nullptr
    if (lhs == nullptr || rhs.data() == nullptr)
    {
        return rhs.data() == lhs;
    }

    return lhs == rhs;
}

template <typename CharT, typename TraitsT, typename AllocatorT>
PHI_NODISCARD constexpr boolean string_equals(
        const CharT* lhs, std::basic_string<CharT, TraitsT, AllocatorT> rhs) noexcept
{
    return lhs == basic_string_view<CharT, TraitsT>(rhs.data(), rhs.length());
}

// phi::basic_string_view - x

template <typename CharT, typename TraitsT>
PHI_NODISCARD constexpr boolean string_equals(basic_string_view<CharT, TraitsT> lhs,
                                              nullptr_t) noexcept
{
    return lhs.is_null();
}

template <typename CharT, typename TraitsT>
PHI_NODISCARD PHI_EXTENDED_CONSTEXPR boolean string_equals(basic_string_view<CharT, TraitsT> lhs,
                                                           const CharT* rhs) noexcept
{
    if (lhs.is_null())
    {
        return rhs == nullptr;
    }
    if (rhs == nullptr)
    {
        return lhs.is_null();
    }

    return lhs == rhs;
}

template <typename CharT, typename TraitsT>
PHI_NODISCARD constexpr boolean string_equals(basic_string_view<CharT, TraitsT> lhs,
                                              basic_string_view<CharT, TraitsT> rhs) noexcept
{
    return lhs == rhs;
}

template <typename CharT, typename TraitsT>
PHI_NODISCARD constexpr boolean string_equals(basic_string_view<CharT, TraitsT>      lhs,
                                              std::basic_string_view<CharT, TraitsT> rhs) noexcept
{
    return lhs == phi::basic_string_view<CharT, TraitsT>(rhs);
}

template <typename CharT, typename TraitsT, typename AllocatorT>
PHI_NODISCARD constexpr boolean string_equals(
        basic_string_view<CharT, TraitsT>             lhs,
        std::basic_string<CharT, TraitsT, AllocatorT> rhs) noexcept
{
    return lhs == basic_string_view<CharT, TraitsT>(rhs.data(), rhs.length());
}

// std::string_view - x

template <typename CharT, typename TraitsT>
PHI_NODISCARD constexpr boolean string_equals(std::basic_string_view<CharT, TraitsT> lhs,
                                              nullptr_t) noexcept
{
    return lhs.data() == nullptr;
}

template <typename CharT, typename TraitsT>
PHI_NODISCARD PHI_EXTENDED_CONSTEXPR boolean
string_equals(std::basic_string_view<CharT, TraitsT> lhs, const CharT* rhs) noexcept
{
    if (lhs.data() == nullptr)
    {
        return lhs.data() == rhs;
    }
    if (rhs == nullptr)
    {
        return lhs.data() == nullptr;
    }

    return lhs == rhs;
}

template <typename CharT, typename TraitsT>
PHI_NODISCARD constexpr boolean string_equals(std::basic_string_view<CharT, TraitsT> lhs,
                                              basic_string_view<CharT, TraitsT>      rhs) noexcept
{
    return phi::basic_string_view<CharT, TraitsT>(lhs) == rhs;
}

template <typename CharT, typename TraitsT>
PHI_NODISCARD constexpr boolean string_equals(std::basic_string_view<CharT, TraitsT> lhs,
                                              std::basic_string_view<CharT, TraitsT> rhs) noexcept
{
    return lhs == rhs;
}

template <typename CharT, typename TraitsT, typename AllocatorT>
PHI_NODISCARD constexpr boolean string_equals(
        std::basic_string_view<CharT, TraitsT>        lhs,
        std::basic_string<CharT, TraitsT, AllocatorT> rhs) noexcept
{
    return phi::basic_string_view<CharT, TraitsT>(lhs) ==
           phi::basic_string_view<CharT, TraitsT>(rhs);
}

// std::basic_string - x

template <typename CharT, typename TraitsT, typename AllocatorT>
PHI_NODISCARD constexpr boolean string_equals(std::basic_string<CharT, TraitsT, AllocatorT> lhs,
                                              nullptr_t) noexcept
{
    return lhs.data() == nullptr;
}

template <typename CharT, typename TraitsT, typename AllocatorT>
PHI_NODISCARD constexpr boolean string_equals(std::basic_string<CharT, TraitsT, AllocatorT> lhs,
                                              const CharT* rhs) noexcept
{
    return basic_string_view<CharT, TraitsT>(lhs.data(), lhs.length()) == rhs;
}

template <typename CharT, typename TraitsT, typename AllocatorT>
PHI_NODISCARD constexpr boolean string_equals(std::basic_string<CharT, TraitsT, AllocatorT> lhs,
                                              basic_string_view<CharT, TraitsT> rhs) noexcept
{
    return basic_string_view<CharT, TraitsT>(lhs.data(), lhs.length()) == rhs;
}

template <typename CharT, typename TraitsT, typename AllocatorT>
PHI_NODISCARD constexpr boolean string_equals(std::basic_string<CharT, TraitsT, AllocatorT> lhs,
                                              std::basic_string_view<CharT, TraitsT> rhs) noexcept
{
    return lhs == rhs;
}

template <typename CharT, typename TraitsT, typename AllocatorT>
PHI_NODISCARD constexpr boolean string_equals(
        std::basic_string<CharT, TraitsT, AllocatorT> lhs,
        std::basic_string<CharT, TraitsT, AllocatorT> rhs) noexcept
{
    return lhs == rhs;
}

// TODO: implement with count

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

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_ALGORITHM_STRING_EQUALS_HPP
