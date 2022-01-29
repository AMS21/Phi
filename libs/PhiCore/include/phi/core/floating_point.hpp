// This file is heavily inspired by Jonathan Müllers <jonathanmueller.dev@gmail.com> type_safe library https://github.com/foonathan/type_safe
// licensed under the MIT license https://github.com/foonathan/type_safe/blob/master/LICENSE
// Original file at https://github.com/foonathan/type_safe/blob/master/include/type_safe/floating_point.hpp
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

#ifndef INCG_PHI_CORE_FLOATING_POINT_HPP
#define INCG_PHI_CORE_FLOATING_POINT_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/algorithm/swap.hpp"
#include "phi/compiler_support/inline.hpp"
#include "phi/compiler_support/inline_variables.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/compiler_support/warning.hpp"
#include "phi/core/boolean.hpp"
#include "phi/type_traits/conditional.hpp"
#include "phi/type_traits/enable_if.hpp"
#include "phi/type_traits/integral_constant.hpp"
#include "phi/type_traits/is_unsafe_floating_point.hpp"
#include <cmath>
#include <functional>
#include <iosfwd>
#include <limits>

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename FloatT>
class floating_point;

/// \cond detail
namespace detail
{
    // Floating point conversion
    template <typename FromT, typename ToT>
    struct is_safe_floating_point_conversion
        : public bool_constant<is_unsafe_floating_point<FromT>::value &&
                               is_unsafe_floating_point<ToT>::value && sizeof(FromT) <= sizeof(ToT)>
    {};

    template <typename FromT, typename ToT>
    using enable_safe_floating_point_conversion =
            enable_if_t<is_safe_floating_point_conversion<FromT, ToT>::value>;

    template <typename FromT, typename ToT>
    using fallback_safe_floating_point_conversion =
            enable_if_t<!is_safe_floating_point_conversion<FromT, ToT>::value>;

    // Floating point comparison
    template <typename LhsT, typename RhsT>
    struct is_safe_floating_point_comparison
        : public bool_constant<is_safe_floating_point_conversion<LhsT, RhsT>::value ||
                               is_safe_floating_point_conversion<RhsT, LhsT>::value>
    {};

    template <typename LhsT, typename RhsT>
    using enable_safe_floating_point_comparison =
            enable_if_t<is_safe_floating_point_comparison<LhsT, RhsT>::value>;

    template <typename LhsT, typename RhsT>
    using fallback_safe_floating_point_comparison =
            enable_if_t<!is_safe_floating_point_comparison<LhsT, RhsT>::value>;

    // Floating point operation
    template <typename LhsT, typename RhsT>
    struct is_safe_floating_point_operation
        : public bool_constant<is_unsafe_floating_point<LhsT>::value &&
                               is_unsafe_floating_point<RhsT>::value>
    {};

    template <typename LhsT, typename RhsT>
    using floating_point_result_t =
            floating_point<enable_if_t<is_safe_floating_point_operation<LhsT, RhsT>::value,
                                       conditional_t<sizeof(LhsT) < sizeof(RhsT), RhsT, LhsT>>>;
} // namespace detail
/// \endcond

template <typename FloatT>
class floating_point
{
    static_assert(is_unsafe_floating_point<FloatT>::value,
                  "[phi::floating_point] must be a floating point type");

public:
    using this_type   = floating_point<FloatT>;
    using value_type  = FloatT;
    using limits_type = std::numeric_limits<FloatT>;

    floating_point() = delete;

    template <typename TypeT,
              typename = detail::enable_safe_floating_point_conversion<TypeT, FloatT>>
    // cppcheck-suppress noExplicitConstructor; NOLINTNEXTLINE(hicpp-explicit-conversions)
    PHI_ALWAYS_INLINE constexpr floating_point(const TypeT& val) noexcept
        : m_Value(static_cast<FloatT>(val))
    {}

    template <typename TypeT,
              typename = detail::enable_safe_floating_point_conversion<TypeT, FloatT>>
    // cppcheck-suppress noExplicitConstructor; NOLINTNEXTLINE(hicpp-explicit-conversions)
    PHI_ALWAYS_INLINE constexpr floating_point(const floating_point<TypeT>& val) noexcept
        : m_Value(static_cast<FloatT>(static_cast<TypeT>(val)))
    {}

    template <typename TypeT,
              typename = detail::fallback_safe_floating_point_conversion<TypeT, FloatT>>
    constexpr floating_point(TypeT) = delete;

    //=== assignment ===//

    template <typename TypeT,
              typename = detail::enable_safe_floating_point_conversion<TypeT, FloatT>>
    PHI_ALWAYS_INLINE floating_point& operator=(const TypeT& val) noexcept
    {
        m_Value = val;
        return *this;
    }

    template <typename TypeT,
              typename = detail::enable_safe_floating_point_conversion<TypeT, FloatT>>
    PHI_ALWAYS_INLINE floating_point& operator=(const floating_point<TypeT>& val) noexcept
    {
        m_Value = static_cast<TypeT>(val);
        return *this;
    }

    template <typename TypeT,
              typename = detail::fallback_safe_floating_point_conversion<TypeT, FloatT>>
    floating_point& operator=(TypeT) = delete;

    //=== conversion back ===//

    PHI_ALWAYS_INLINE explicit constexpr operator FloatT() const noexcept
    {
        return m_Value;
    }

    PHI_NODISCARD PHI_ALWAYS_INLINE constexpr FloatT get() const noexcept
    {
        return m_Value;
    }

    PHI_EXTENDED_CONSTEXPR void swap(floating_point<FloatT>& other) noexcept
    {
        phi::swap(m_Value, other.m_Value);
    }

    //=== unary operators ===//

    PHI_ALWAYS_INLINE constexpr floating_point operator+() const noexcept
    {
        return *this;
    }

    PHI_ALWAYS_INLINE constexpr floating_point operator-() const noexcept
    {
        return -m_Value;
    }

    //=== compound assignment ====//

    template <typename TypeT,
              typename = detail::enable_safe_floating_point_conversion<TypeT, FloatT>>
    PHI_ALWAYS_INLINE floating_point& operator+=(const floating_point<TypeT>& other) noexcept
    {
        m_Value += static_cast<TypeT>(other);
        return *this;
    }

    template <typename TypeT,
              typename = detail::enable_safe_floating_point_conversion<TypeT, FloatT>>
    PHI_ALWAYS_INLINE floating_point& operator+=(const TypeT& other) noexcept
    {
        return *this += floating_point<TypeT>(other);
    }

    template <typename TypeT,
              typename = detail::fallback_safe_floating_point_conversion<TypeT, FloatT>>
    floating_point& operator+=(floating_point<TypeT>) = delete;

    template <typename TypeT,
              typename = detail::fallback_safe_floating_point_conversion<TypeT, FloatT>>
    floating_point& operator+=(TypeT) = delete;

    template <typename TypeT,
              typename = detail::enable_safe_floating_point_conversion<TypeT, FloatT>>
    PHI_ALWAYS_INLINE floating_point& operator-=(const floating_point<TypeT>& other) noexcept
    {
        m_Value -= static_cast<TypeT>(other);
        return *this;
    }

    template <typename TypeT,
              typename = detail::enable_safe_floating_point_conversion<TypeT, FloatT>>
    PHI_ALWAYS_INLINE floating_point& operator-=(const TypeT& other) noexcept
    {
        return *this -= floating_point<TypeT>(other);
    }

    template <typename TypeT,
              typename = detail::fallback_safe_floating_point_conversion<TypeT, FloatT>>
    floating_point& operator-=(floating_point<TypeT>) = delete;

    template <typename TypeT,
              typename = detail::fallback_safe_floating_point_conversion<TypeT, FloatT>>
    floating_point& operator-=(TypeT) = delete;

    template <typename TypeT,
              typename = detail::enable_safe_floating_point_conversion<TypeT, FloatT>>
    PHI_ALWAYS_INLINE floating_point& operator*=(const floating_point<TypeT>& other) noexcept
    {
        m_Value *= static_cast<TypeT>(other);
        return *this;
    }

    template <typename TypeT,
              typename = detail::enable_safe_floating_point_conversion<TypeT, FloatT>>
    PHI_ALWAYS_INLINE floating_point& operator*=(const TypeT& other) noexcept
    {
        return *this *= floating_point<TypeT>(other);
    }

    template <typename TypeT,
              typename = detail::fallback_safe_floating_point_conversion<TypeT, FloatT>>
    floating_point& operator*=(floating_point<TypeT>) = delete;

    template <typename TypeT,
              typename = detail::fallback_safe_floating_point_conversion<TypeT, FloatT>>
    floating_point& operator*=(TypeT) = delete;

    template <typename TypeT,
              typename = detail::enable_safe_floating_point_conversion<TypeT, FloatT>>
    PHI_ALWAYS_INLINE floating_point& operator/=(const floating_point<TypeT>& other) noexcept
    {
        m_Value /= static_cast<TypeT>(other);
        return *this;
    }

    template <typename TypeT,
              typename = detail::enable_safe_floating_point_conversion<TypeT, FloatT>>
    PHI_ALWAYS_INLINE floating_point& operator/=(const TypeT& other) noexcept
    {
        return *this /= floating_point<TypeT>(other);
    }

    template <typename TypeT,
              typename = detail::fallback_safe_floating_point_conversion<TypeT, FloatT>>
    floating_point& operator/=(floating_point<TypeT>) = delete;

    template <typename TypeT,
              typename = detail::fallback_safe_floating_point_conversion<TypeT, FloatT>>
    floating_point& operator/=(TypeT) = delete;

    template <typename TypeT,
              typename = detail::enable_safe_floating_point_conversion<TypeT, FloatT>>
    PHI_ALWAYS_INLINE floating_point& operator%=(const floating_point<TypeT>& other) noexcept
    {
        m_Value = std::fmod(m_Value, static_cast<TypeT>(other));
        return *this;
    }

    template <typename TypeT,
              typename = detail::enable_safe_floating_point_conversion<TypeT, FloatT>>
    PHI_ALWAYS_INLINE floating_point& operator%=(const TypeT& other) noexcept
    {
        return *this %= floating_point<TypeT>(other);
    }

    template <typename TypeT,
              typename = detail::fallback_safe_floating_point_conversion<TypeT, FloatT>>
    floating_point& operator%=(floating_point<TypeT>) = delete;

    template <typename TypeT,
              typename = detail::fallback_safe_floating_point_conversion<TypeT, FloatT>>
    floating_point& operator%=(TypeT) = delete;

private:
    FloatT m_Value; /// Wraped float value
};

//=== comparison ===//

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_floating_point_comparison<LhsT, RhsT>>
PHI_ALWAYS_INLINE constexpr boolean operator<(const floating_point<LhsT>& lhs,
                                              const floating_point<RhsT>& rhs) noexcept
{
    return static_cast<LhsT>(lhs) < static_cast<RhsT>(rhs);
}

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_floating_point_conversion<LhsT, RhsT>>
PHI_ALWAYS_INLINE constexpr boolean operator<(const LhsT&                 lhs,
                                              const floating_point<RhsT>& rhs) noexcept
{
    return floating_point<LhsT>(lhs) < rhs;
}

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_floating_point_comparison<LhsT, RhsT>>
PHI_ALWAYS_INLINE constexpr boolean operator<(const floating_point<LhsT>& lhs,
                                              const RhsT&                 rhs) noexcept
{
    return lhs < floating_point<RhsT>(rhs);
}

template <typename LhsT, typename RhsT,
          typename = detail::fallback_safe_floating_point_comparison<LhsT, RhsT>>
constexpr boolean operator<(floating_point<LhsT>, floating_point<RhsT>) = delete;

template <typename LhsT, typename RhsT,
          typename = detail::fallback_safe_floating_point_comparison<LhsT, RhsT>>
constexpr boolean operator<(LhsT, floating_point<RhsT>) = delete;

template <typename LhsT, typename RhsT,
          typename = detail::fallback_safe_floating_point_comparison<LhsT, RhsT>>
constexpr boolean operator<(floating_point<LhsT>, RhsT) = delete;

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_floating_point_comparison<LhsT, RhsT>>
PHI_ALWAYS_INLINE constexpr boolean operator<=(const floating_point<LhsT>& lhs,
                                               const floating_point<RhsT>& rhs) noexcept
{
    return static_cast<LhsT>(lhs) <= static_cast<RhsT>(rhs);
}

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_floating_point_conversion<LhsT, RhsT>>
PHI_ALWAYS_INLINE constexpr boolean operator<=(const LhsT&                 lhs,
                                               const floating_point<RhsT>& rhs) noexcept
{
    return floating_point<LhsT>(lhs) <= rhs;
}

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_floating_point_comparison<LhsT, RhsT>>
PHI_ALWAYS_INLINE constexpr boolean operator<=(const floating_point<LhsT>& lhs,
                                               const RhsT&                 rhs) noexcept
{
    return lhs <= floating_point<RhsT>(rhs);
}

template <typename LhsT, typename RhsT,
          typename = detail::fallback_safe_floating_point_comparison<LhsT, RhsT>>
constexpr boolean operator<=(floating_point<LhsT>, floating_point<RhsT>) = delete;

template <typename LhsT, typename RhsT,
          typename = detail::fallback_safe_floating_point_comparison<LhsT, RhsT>>
constexpr boolean operator<=(LhsT, floating_point<RhsT>) = delete;

template <typename LhsT, typename RhsT,
          typename = detail::fallback_safe_floating_point_comparison<LhsT, RhsT>>
constexpr boolean operator<=(floating_point<LhsT>, RhsT) = delete;

PHI_CLANG_SUPPRESS_WARNING_PUSH()
PHI_CLANG_SUPPRESS_WARNING("-Wdouble-promotion")

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_floating_point_comparison<LhsT, RhsT>>
PHI_ALWAYS_INLINE constexpr boolean operator>(const floating_point<LhsT>& lhs,
                                              const floating_point<RhsT>& rhs) noexcept
{
    return static_cast<LhsT>(lhs) > static_cast<RhsT>(rhs);
}

PHI_CLANG_SUPPRESS_WARNING_POP()

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_floating_point_conversion<LhsT, RhsT>>
PHI_ALWAYS_INLINE constexpr boolean operator>(const LhsT&                 lhs,
                                              const floating_point<RhsT>& rhs) noexcept
{
    return floating_point<LhsT>(lhs) > rhs;
}

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_floating_point_comparison<LhsT, RhsT>>
PHI_ALWAYS_INLINE constexpr boolean operator>(const floating_point<LhsT>& lhs,
                                              const RhsT&                 rhs) noexcept
{
    return lhs > floating_point<RhsT>(rhs);
}

template <typename LhsT, typename RhsT,
          typename = detail::fallback_safe_floating_point_comparison<LhsT, RhsT>>
constexpr boolean operator>(floating_point<LhsT>, floating_point<RhsT>) = delete;

template <typename LhsT, typename RhsT,
          typename = detail::fallback_safe_floating_point_comparison<LhsT, RhsT>>
constexpr boolean operator>(LhsT, floating_point<RhsT>) = delete;

template <typename LhsT, typename RhsT,
          typename = detail::fallback_safe_floating_point_comparison<LhsT, RhsT>>
constexpr boolean operator>(floating_point<LhsT>, RhsT) = delete;

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_floating_point_comparison<LhsT, RhsT>>
PHI_ALWAYS_INLINE constexpr boolean operator>=(const floating_point<LhsT>& lhs,
                                               const floating_point<RhsT>& rhs) noexcept
{
    return static_cast<LhsT>(lhs) >= static_cast<RhsT>(rhs);
}

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_floating_point_conversion<LhsT, RhsT>>
PHI_ALWAYS_INLINE constexpr boolean operator>=(const LhsT&                 lhs,
                                               const floating_point<RhsT>& rhs) noexcept
{
    return floating_point<LhsT>(lhs) >= rhs;
}

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_floating_point_comparison<LhsT, RhsT>>
PHI_ALWAYS_INLINE constexpr boolean operator>=(const floating_point<LhsT>& lhs,
                                               const RhsT&                 rhs) noexcept
{
    return lhs >= floating_point<RhsT>(rhs);
}

template <typename LhsT, typename RhsT,
          typename = detail::fallback_safe_floating_point_comparison<LhsT, RhsT>>
constexpr boolean operator>=(floating_point<LhsT>, floating_point<RhsT>) = delete;

template <typename LhsT, typename RhsT,
          typename = detail::fallback_safe_floating_point_comparison<LhsT, RhsT>>
constexpr boolean operator>=(LhsT, floating_point<RhsT>) = delete;

template <typename LhsT, typename RhsT,
          typename = detail::fallback_safe_floating_point_comparison<LhsT, RhsT>>
constexpr boolean operator>=(floating_point<LhsT>, RhsT) = delete;

//=== binary operations ===//

template <typename LhsT, typename RhsT>
PHI_ALWAYS_INLINE constexpr auto operator+(const floating_point<LhsT>& lhs,
                                           const floating_point<RhsT>& rhs) noexcept
        -> detail::floating_point_result_t<LhsT, RhsT>
{
    return static_cast<LhsT>(lhs) + static_cast<RhsT>(rhs);
}

template <typename LhsT, typename RhsT>
PHI_ALWAYS_INLINE constexpr auto operator+(const LhsT&                 lhs,
                                           const floating_point<RhsT>& rhs) noexcept
        -> detail::floating_point_result_t<LhsT, RhsT>
{
    return floating_point<LhsT>(lhs) + rhs;
}

template <typename LhsT, typename RhsT>
PHI_ALWAYS_INLINE constexpr auto operator+(const floating_point<LhsT>& lhs,
                                           const RhsT&                 rhs) noexcept
        -> detail::floating_point_result_t<LhsT, RhsT>
{
    return lhs + floating_point<RhsT>(rhs);
}

template <typename LhsT, typename RhsT>
PHI_ALWAYS_INLINE constexpr auto operator-(const floating_point<LhsT>& lhs,
                                           const floating_point<RhsT>& rhs) noexcept
        -> detail::floating_point_result_t<LhsT, RhsT>
{
    return static_cast<LhsT>(lhs) - static_cast<RhsT>(rhs);
}

template <typename LhsT, typename RhsT>
PHI_ALWAYS_INLINE constexpr auto operator-(const LhsT&                 lhs,
                                           const floating_point<RhsT>& rhs) noexcept
        -> detail::floating_point_result_t<LhsT, RhsT>
{
    return floating_point<LhsT>(lhs) - rhs;
}

template <typename LhsT, typename RhsT>
PHI_ALWAYS_INLINE constexpr auto operator-(const floating_point<LhsT>& lhs,
                                           const RhsT&                 rhs) noexcept
        -> detail::floating_point_result_t<LhsT, RhsT>
{
    return lhs - floating_point<RhsT>(rhs);
}

template <typename LhsT, typename RhsT>
PHI_ALWAYS_INLINE constexpr auto operator*(const floating_point<LhsT>& lhs,
                                           const floating_point<RhsT>& rhs) noexcept
        -> detail::floating_point_result_t<LhsT, RhsT>
{
    return static_cast<LhsT>(lhs) * static_cast<RhsT>(rhs);
}

template <typename LhsT, typename RhsT>
PHI_ALWAYS_INLINE constexpr auto operator*(const LhsT&                 lhs,
                                           const floating_point<RhsT>& rhs) noexcept
        -> detail::floating_point_result_t<LhsT, RhsT>
{
    return floating_point<LhsT>(lhs) * rhs;
}

template <typename LhsT, typename RhsT>
PHI_ALWAYS_INLINE constexpr auto operator*(const floating_point<LhsT>& lhs,
                                           const RhsT&                 rhs) noexcept
        -> detail::floating_point_result_t<LhsT, RhsT>
{
    return lhs * floating_point<RhsT>(rhs);
}

template <typename LhsT, typename RhsT>
PHI_ALWAYS_INLINE constexpr auto operator/(const floating_point<LhsT>& lhs,
                                           const floating_point<RhsT>& rhs) noexcept
        -> detail::floating_point_result_t<LhsT, RhsT>
{
    return static_cast<LhsT>(lhs) / static_cast<RhsT>(rhs);
}

template <typename LhsT, typename RhsT>
PHI_ALWAYS_INLINE constexpr auto operator/(const LhsT&                 lhs,
                                           const floating_point<RhsT>& rhs) noexcept
        -> detail::floating_point_result_t<LhsT, RhsT>
{
    return floating_point<LhsT>(lhs) / rhs;
}

template <typename LhsT, typename RhsT>
PHI_ALWAYS_INLINE constexpr auto operator/(const floating_point<LhsT>& lhs,
                                           const RhsT&                 rhs) noexcept
        -> detail::floating_point_result_t<LhsT, RhsT>
{
    return lhs / floating_point<RhsT>(rhs);
}

template <typename LhsT, typename RhsT>
PHI_ALWAYS_INLINE constexpr auto operator%(const floating_point<LhsT>& lhs,
                                           const floating_point<RhsT>& rhs) noexcept
        -> detail::floating_point_result_t<LhsT, RhsT>
{
    return std::fmod(static_cast<LhsT>(lhs), static_cast<RhsT>(rhs));
}

template <typename LhsT, typename RhsT>
PHI_ALWAYS_INLINE constexpr auto operator%(const LhsT&                 lhs,
                                           const floating_point<RhsT>& rhs) noexcept
        -> detail::floating_point_result_t<LhsT, RhsT>
{
    return floating_point<LhsT>(lhs) % rhs;
}

template <typename LhsT, typename RhsT>
PHI_ALWAYS_INLINE constexpr auto operator%(const floating_point<LhsT>& lhs,
                                           const RhsT&                 rhs) noexcept
        -> detail::floating_point_result_t<LhsT, RhsT>
{
    return lhs % floating_point<RhsT>(rhs);
}

//=== input/output ===/

template <typename CharT, class CharTraitsT, typename FloatT>
std::basic_istream<CharT, CharTraitsT>& operator>>(std::basic_istream<CharT, CharTraitsT>& in,
                                                   floating_point<FloatT>&                 f)
{
    FloatT val{FloatT(0.0)};
    in >> val;
    f = val;
    return in;
}

template <typename CharT, class CharTraitsT, typename FloatT>
std::basic_ostream<CharT, CharTraitsT>& operator<<(std::basic_ostream<CharT, CharTraitsT>& out,
                                                   const floating_point<FloatT>&           f)
{
    return out << static_cast<FloatT>(f);
}

template <typename FloatT>
PHI_EXTENDED_CONSTEXPR_OR_INLINE void swap(floating_point<FloatT>& lhs,
                                           floating_point<FloatT>& rhs) noexcept
{
    lhs.swap(rhs);
}

DETAIL_PHI_END_NAMESPACE()

namespace std
{
    template <typename FloatT>
    struct hash<phi::floating_point<FloatT>>
    {
        std::size_t operator()(const phi::floating_point<FloatT>& value) const noexcept
        {
            return std::hash<FloatT>()(static_cast<FloatT>(value));
        }
    };

    template <typename FloatT>
    struct numeric_limits<phi::floating_point<FloatT>> : std::numeric_limits<FloatT>
    {};
} // namespace std

#endif // INCG_PHI_CORE_FLOATING_POINT_HPP
