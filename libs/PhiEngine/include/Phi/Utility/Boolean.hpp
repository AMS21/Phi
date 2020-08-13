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

#ifndef INCG_PHI_UTILITY_BOOLEAN_HPP
#define INCG_PHI_UTILITY_BOOLEAN_HPP

#include "Phi/PhiConfig.hpp"
#include <cpp/Implicit.hpp>
#include <cpp/Inline.hpp>
#include <functional>
#include <iosfwd>
#include <type_traits>
#include <utility>

DETAIL_PHI_BEGIN_NAMESPACE()

class Boolean;

/// \cond detail
namespace detail
{
    template <typename TypeT>
    struct is_boolean : std::false_type
    {};

    template <>
    struct is_boolean<bool> : std::true_type
    {};

    template <>
    struct is_boolean<Boolean> : std::true_type
    {};

    template <typename TypeT>
    constexpr inline bool IsBooleanV = is_boolean<TypeT>::value;

    template <typename TypeT>
    using enable_if_boolean_t = typename std::enable_if_t<IsBooleanV<TypeT>>;
} // namespace detail
/// \endcond

class Boolean
{
public:
    Boolean() = delete;

    template <typename TypeT, typename = detail::enable_if_boolean_t<TypeT>>
    // cppcheck-suppress noExplicitConstructor; NOLINTNEXTLINE(hicpp-explicit-conversions)
    CPP_IMPLICIT CPP_ALWAYS_INLINE constexpr Boolean(TypeT value) noexcept
        : m_Value(value)
    {}

    template <typename TypeT, typename = detail::enable_if_boolean_t<TypeT>>
    CPP_ALWAYS_INLINE Boolean& operator=(TypeT value) noexcept
    {
        m_Value = value;
        return *this;
    }

    CPP_ALWAYS_INLINE constexpr explicit operator bool() const noexcept
    {
        return m_Value;
    }

    CPP_ALWAYS_INLINE constexpr Boolean operator!() const noexcept
    {
        return Boolean(!m_Value);
    }

    [[nodiscard]] CPP_ALWAYS_INLINE constexpr bool get() const noexcept
    {
        return m_Value;
    }

private:
    bool m_Value; /// The Wrapped bool value
};

CPP_ALWAYS_INLINE constexpr bool operator==(const Boolean& lhs, const Boolean& rhs) noexcept
{
    return static_cast<bool>(lhs) == static_cast<bool>(rhs);
}

template <typename TypeT, typename = detail::enable_if_boolean_t<TypeT>>
CPP_ALWAYS_INLINE constexpr bool operator==(const Boolean& lhs, TypeT rhs) noexcept
{
    return static_cast<bool>(lhs) == static_cast<bool>(rhs);
}

template <typename TypeT, typename = detail::enable_if_boolean_t<TypeT>>
CPP_ALWAYS_INLINE constexpr bool operator==(TypeT lhs, const Boolean& rhs) noexcept
{
    return static_cast<bool>(lhs) == static_cast<bool>(rhs);
}

CPP_ALWAYS_INLINE constexpr bool operator!=(const Boolean& lhs, const Boolean& rhs) noexcept
{
    return static_cast<bool>(lhs) != static_cast<bool>(rhs);
}

template <typename TypeT, typename = detail::enable_if_boolean_t<TypeT>>
CPP_ALWAYS_INLINE constexpr bool operator!=(const Boolean& lhs, TypeT rhs) noexcept
{
    return static_cast<bool>(lhs) != static_cast<bool>(rhs);
}

template <typename TypeT, typename = detail::enable_if_boolean_t<TypeT>>
CPP_ALWAYS_INLINE constexpr bool operator!=(TypeT lhs, const Boolean& rhs) noexcept
{
    return static_cast<bool>(lhs) != static_cast<bool>(rhs);
}

template <typename CharT, typename CharTraitsT>
std::basic_istream<CharT, CharTraitsT>& operator>>(std::basic_istream<CharT, CharTraitsT>& stream,
                                                   Boolean&                                rhs)
{
    bool val{false};
    stream >> val;
    rhs = val;

    return stream;
}

template <typename CharT, typename CharTraitsT>
std::basic_ostream<CharT, CharTraitsT>& operator<<(std::basic_ostream<CharT, CharTraitsT>& stream,
                                                   const Boolean&                          value)
{
    return stream << static_cast<bool>(value);
}

DETAIL_PHI_END_NAMESPACE()

namespace std
{
    /// Hash specialization for [phi::Boolean]().
    template <>
    struct hash<phi::Boolean>
    {
        std::size_t operator()(phi::Boolean value) const noexcept
        {
            return std::hash<bool>()(static_cast<bool>(value));
        }
    };
} // namespace std

#endif // INCG_PHI_UTILITY_BOOLEAN_HPP
