// This file is heavily inspired by Jonathan Müllers <jonathanmueller.dev@gmail.com> type_safe library https://github.com/foonathan/type_safe
// licensed under the MIT license https://github.com/foonathan/type_safe/blob/master/LICENSE
// Original file at https://github.com/foonathan/type_safe/blob/master/include/type_safe/boolean.hpp
/* MIT License

Copyright (c) 2016-2020 Jonathan Müller

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef INCG_PHI_CORE_BOOLEAN_HPP
#define INCG_PHI_CORE_BOOLEAN_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/algorithm/swap.hpp"
#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/inline.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/compiler_support/noexcept.hpp"
#include "phi/compiler_support/standard_library.hpp"
#include "phi/type_traits/enable_if.hpp"
#include "phi/type_traits/is_bool.hpp"
#include <functional>
#include <iosfwd>
#include <limits>

DETAIL_PHI_BEGIN_NAMESPACE()

/// \cond detail
namespace detail
{
    template <typename TypeT>
    using enable_if_boolean_t = enable_if_t<is_bool<TypeT>::value>;
} // namespace detail
/// \endcond

class boolean
{
public:
    using this_type   = boolean;
    using value_type  = bool;
    using limits_type = std::numeric_limits<bool>;

    boolean() = delete;

    template <typename TypeT, typename = detail::enable_if_boolean_t<TypeT>>
    // cppcheck-suppress noExplicitConstructor
    PHI_ALWAYS_INLINE PHI_CONSTEXPR boolean(TypeT value) PHI_NOEXCEPT : m_Value(value)
    {}

    template <typename TypeT, typename = detail::enable_if_boolean_t<TypeT>>
    PHI_ALWAYS_INLINE PHI_CONSTEXPR boolean& operator=(TypeT value) PHI_NOEXCEPT
    {
        m_Value = value;
        return *this;
    }

    PHI_ALWAYS_INLINE PHI_CONSTEXPR explicit operator bool() const PHI_NOEXCEPT
    {
        return m_Value;
    }

    PHI_ALWAYS_INLINE PHI_CONSTEXPR boolean operator!() const PHI_NOEXCEPT
    {
        return {!m_Value};
    }

    PHI_NODISCARD PHI_ALWAYS_INLINE PHI_CONSTEXPR bool unsafe() const PHI_NOEXCEPT
    {
        return m_Value;
    }

    PHI_ALWAYS_INLINE PHI_CONSTEXPR void flip() PHI_NOEXCEPT
    {
        m_Value = !m_Value;
    }

    PHI_NODISCARD PHI_ALWAYS_INLINE PHI_CONSTEXPR boolean as_flipped() const PHI_NOEXCEPT
    {
        return boolean{!m_Value};
    }

    PHI_EXTENDED_CONSTEXPR void swap(boolean& other) PHI_NOEXCEPT
    {
        phi::swap(m_Value, other.m_Value);
    }

private:
    bool m_Value; /// The Wrapped bool value
};

PHI_ALWAYS_INLINE PHI_CONSTEXPR boolean operator==(const boolean& lhs,
                                                   const boolean& rhs) PHI_NOEXCEPT
{
    return {static_cast<bool>(lhs) == static_cast<bool>(rhs)};
}

template <typename TypeT, typename = detail::enable_if_boolean_t<TypeT>>
PHI_ALWAYS_INLINE PHI_CONSTEXPR boolean operator==(const boolean& lhs, TypeT rhs) PHI_NOEXCEPT
{
    return {static_cast<bool>(lhs) == static_cast<bool>(rhs)};
}

template <typename TypeT, typename = detail::enable_if_boolean_t<TypeT>>
PHI_ALWAYS_INLINE PHI_CONSTEXPR boolean operator==(TypeT lhs, const boolean& rhs) PHI_NOEXCEPT
{
    return {static_cast<bool>(lhs) == static_cast<bool>(rhs)};
}

PHI_ALWAYS_INLINE PHI_CONSTEXPR boolean operator!=(const boolean& lhs,
                                                   const boolean& rhs) PHI_NOEXCEPT
{
    return {static_cast<bool>(lhs) != static_cast<bool>(rhs)};
}

template <typename TypeT, typename = detail::enable_if_boolean_t<TypeT>>
PHI_ALWAYS_INLINE PHI_CONSTEXPR boolean operator!=(const boolean& lhs, TypeT rhs) PHI_NOEXCEPT
{
    return {static_cast<bool>(lhs) != static_cast<bool>(rhs)};
}

template <typename TypeT, typename = detail::enable_if_boolean_t<TypeT>>
PHI_ALWAYS_INLINE PHI_CONSTEXPR boolean operator!=(TypeT lhs, const boolean& rhs) PHI_NOEXCEPT
{
    return {static_cast<bool>(lhs) != static_cast<bool>(rhs)};
}

template <typename CharT, typename CharTraitsT>
std::basic_istream<CharT, CharTraitsT>& operator>>(std::basic_istream<CharT, CharTraitsT>& stream,
                                                   boolean&                                rhs)
{
    bool val{false};
    stream >> val;
    rhs = val;

    return stream;
}

template <typename CharT, typename CharTraitsT>
std::basic_ostream<CharT, CharTraitsT>& operator<<(std::basic_ostream<CharT, CharTraitsT>& stream,
                                                   const boolean&                          value)
{
    return stream << static_cast<bool>(value);
}

PHI_EXTENDED_CONSTEXPR PHI_ALWAYS_INLINE void swap(boolean& lhs, boolean& rhs) PHI_NOEXCEPT
{
    lhs.swap(rhs);
}

DETAIL_PHI_END_NAMESPACE()

DETAIL_PHI_BEGIN_STD_NAMESPACE()

/// Hash specialization for [phi::boolean]().
template <>
struct hash<phi::boolean>
{
    phi::size_t operator()(phi::boolean value) const PHI_NOEXCEPT
    {
        return std::hash<bool>()(static_cast<bool>(value));
    }
};

template <>
struct numeric_limits<phi::boolean> : public std::numeric_limits<bool>
{};

DETAIL_PHI_END_STD_NAMESPACE()

#endif // INCG_PHI_CORE_BOOLEAN_HPP
