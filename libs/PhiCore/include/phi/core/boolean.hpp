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

#include "phi/compiler_support/inline.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/type_traits/enable_if.hpp"
#include "phi/type_traits/is_bool.hpp"
#include <functional>
#include <iosfwd>
#include <limits>
#include <utility>

DETAIL_PHI_BEGIN_NAMESPACE()

class boolean;

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
    // cppcheck-suppress noExplicitConstructor; NOLINTNEXTLINE(hicpp-explicit-conversions)
    PHI_ALWAYS_INLINE constexpr boolean(TypeT value) noexcept
        : m_Value(value)
    {}

    template <typename TypeT, typename = detail::enable_if_boolean_t<TypeT>>
    PHI_ALWAYS_INLINE boolean& operator=(TypeT value) noexcept
    {
        m_Value = value;
        return *this;
    }

    // NOLINTNEXTLINE(hicpp-explicit-conversions)
    PHI_ALWAYS_INLINE constexpr operator bool() const noexcept
    {
        return m_Value;
    }

    PHI_ALWAYS_INLINE constexpr boolean operator!() const noexcept
    {
        return {!m_Value};
    }

    PHI_NODISCARD PHI_ALWAYS_INLINE constexpr bool get() const noexcept
    {
        return m_Value;
    }

private:
    bool m_Value; /// The Wrapped bool value
};

PHI_ALWAYS_INLINE constexpr boolean operator==(const boolean& lhs, const boolean& rhs) noexcept
{
    return boolean(static_cast<bool>(lhs) == static_cast<bool>(rhs));
}

template <typename TypeT, typename = detail::enable_if_boolean_t<TypeT>>
PHI_ALWAYS_INLINE constexpr boolean operator==(const boolean& lhs, TypeT rhs) noexcept
{
    return boolean(static_cast<bool>(lhs) == static_cast<bool>(rhs));
}

template <typename TypeT, typename = detail::enable_if_boolean_t<TypeT>>
PHI_ALWAYS_INLINE constexpr boolean operator==(TypeT lhs, const boolean& rhs) noexcept
{
    return boolean(static_cast<bool>(lhs) == static_cast<bool>(rhs));
}

PHI_ALWAYS_INLINE constexpr boolean operator!=(const boolean& lhs, const boolean& rhs) noexcept
{
    return boolean(static_cast<bool>(lhs) != static_cast<bool>(rhs));
}

template <typename TypeT, typename = detail::enable_if_boolean_t<TypeT>>
PHI_ALWAYS_INLINE constexpr boolean operator!=(const boolean& lhs, TypeT rhs) noexcept
{
    return boolean(static_cast<bool>(lhs) != static_cast<bool>(rhs));
}

template <typename TypeT, typename = detail::enable_if_boolean_t<TypeT>>
PHI_ALWAYS_INLINE constexpr boolean operator!=(TypeT lhs, const boolean& rhs) noexcept
{
    return boolean(static_cast<bool>(lhs) != static_cast<bool>(rhs));
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

DETAIL_PHI_END_NAMESPACE()

namespace std
{
    /// Hash specialization for [phi::boolean]().
    template <>
    struct hash<phi::boolean>
    {
        std::size_t operator()(phi::boolean value) const noexcept
        {
            return std::hash<bool>()(static_cast<bool>(value));
        }
    };

    template <>
    struct numeric_limits<phi::boolean> : std::numeric_limits<bool>
    {};
} // namespace std

#endif // INCG_PHI_CORE_BOOLEAN_HPP
