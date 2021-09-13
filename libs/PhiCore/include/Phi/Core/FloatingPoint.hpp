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

#ifndef INCG_PHI_UTILITY_FLOATINGPOINT_HPP
#define INCG_PHI_UTILITY_FLOATINGPOINT_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/CompilerSupport/Nodiscard.hpp"
#include "Phi/Config/Inline.hpp"
#include "Phi/Config/Warning.hpp"
#include "Phi/Core/Boolean.hpp"
#include "Phi/TypeTraits/conditional.hpp"
#include "Phi/TypeTraits/enable_if.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"
#include "Phi/TypeTraits/is_unsafe_floating_point.hpp"
#include <cmath>
#include <functional>
#include <iosfwd>
#include <limits>

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename FloatT>
class FloatingPoint;

/// \cond detail
namespace detail
{
    // Floating point conversion
    template <typename FromT, typename ToT>
    struct is_safe_floating_point_conversion
        : public bool_constant<is_unsafe_floating_point_v<FromT> &&
                               is_unsafe_floating_point_v<ToT> && sizeof(FromT) <= sizeof(ToT)>
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
        : public bool_constant<is_unsafe_floating_point_v<LhsT> && is_unsafe_floating_point_v<RhsT>>
    {};

    template <typename LhsT, typename RhsT>
    using floating_point_result_t =
            FloatingPoint<enable_if_t<is_safe_floating_point_operation<LhsT, RhsT>::value,
                                      conditional_t<sizeof(LhsT) < sizeof(RhsT), RhsT, LhsT>>>;
} // namespace detail
/// \endcond

template <typename FloatT>
class FloatingPoint
{
    static_assert(is_unsafe_floating_point<FloatT>::value,
                  "[phi::FloatingPoint] must be a floating point type");

public:
    using this_type   = FloatingPoint<FloatT>;
    using value_type  = FloatT;
    using limits_type = std::numeric_limits<FloatT>;

    FloatingPoint() = delete;

    template <typename TypeT,
              typename = detail::enable_safe_floating_point_conversion<TypeT, FloatT>>
    // cppcheck-suppress noExplicitConstructor; NOLINTNEXTLINE(hicpp-explicit-conversions)
    PHI_ALWAYS_INLINE constexpr FloatingPoint(const TypeT& val) noexcept
        : m_Value(static_cast<FloatT>(val))
    {}

    template <typename TypeT,
              typename = detail::enable_safe_floating_point_conversion<TypeT, FloatT>>
    // cppcheck-suppress noExplicitConstructor; NOLINTNEXTLINE(hicpp-explicit-conversions)
    PHI_ALWAYS_INLINE constexpr FloatingPoint(const FloatingPoint<TypeT>& val) noexcept
        : m_Value(static_cast<FloatT>(static_cast<TypeT>(val)))
    {}

    template <typename TypeT,
              typename = detail::fallback_safe_floating_point_conversion<TypeT, FloatT>>
    constexpr FloatingPoint(TypeT) = delete;

    //=== assignment ===//

    template <typename TypeT,
              typename = detail::enable_safe_floating_point_conversion<TypeT, FloatT>>
    PHI_ALWAYS_INLINE FloatingPoint& operator=(const TypeT& val) noexcept
    {
        m_Value = val;
        return *this;
    }

    template <typename TypeT,
              typename = detail::enable_safe_floating_point_conversion<TypeT, FloatT>>
    PHI_ALWAYS_INLINE FloatingPoint& operator=(const FloatingPoint<TypeT>& val) noexcept
    {
        m_Value = static_cast<TypeT>(val);
        return *this;
    }

    template <typename TypeT,
              typename = detail::fallback_safe_floating_point_conversion<TypeT, FloatT>>
    FloatingPoint& operator=(TypeT) = delete;

    //=== conversion back ===//

    PHI_ALWAYS_INLINE explicit constexpr operator FloatT() const noexcept
    {
        return m_Value;
    }

    PHI_NODISCARD PHI_ALWAYS_INLINE constexpr FloatT get() const noexcept
    {
        return m_Value;
    }

    //=== unary operators ===//

    PHI_ALWAYS_INLINE constexpr FloatingPoint operator+() const noexcept
    {
        return *this;
    }

    PHI_ALWAYS_INLINE constexpr FloatingPoint operator-() const noexcept
    {
        return -m_Value;
    }

    //=== compound assignment ====//

    template <typename TypeT,
              typename = detail::enable_safe_floating_point_conversion<TypeT, FloatT>>
    PHI_ALWAYS_INLINE FloatingPoint& operator+=(const FloatingPoint<TypeT>& other) noexcept
    {
        m_Value += static_cast<TypeT>(other);
        return *this;
    }

    template <typename TypeT,
              typename = detail::enable_safe_floating_point_conversion<TypeT, FloatT>>
    PHI_ALWAYS_INLINE FloatingPoint& operator+=(const TypeT& other) noexcept
    {
        return *this += FloatingPoint<TypeT>(other);
    }

    template <typename TypeT,
              typename = detail::fallback_safe_floating_point_conversion<TypeT, FloatT>>
    FloatingPoint& operator+=(FloatingPoint<TypeT>) = delete;

    template <typename TypeT,
              typename = detail::fallback_safe_floating_point_conversion<TypeT, FloatT>>
    FloatingPoint& operator+=(TypeT) = delete;

    template <typename TypeT,
              typename = detail::enable_safe_floating_point_conversion<TypeT, FloatT>>
    PHI_ALWAYS_INLINE FloatingPoint& operator-=(const FloatingPoint<TypeT>& other) noexcept
    {
        m_Value -= static_cast<TypeT>(other);
        return *this;
    }

    template <typename TypeT,
              typename = detail::enable_safe_floating_point_conversion<TypeT, FloatT>>
    PHI_ALWAYS_INLINE FloatingPoint& operator-=(const TypeT& other) noexcept
    {
        return *this -= FloatingPoint<TypeT>(other);
    }

    template <typename TypeT,
              typename = detail::fallback_safe_floating_point_conversion<TypeT, FloatT>>
    FloatingPoint& operator-=(FloatingPoint<TypeT>) = delete;

    template <typename TypeT,
              typename = detail::fallback_safe_floating_point_conversion<TypeT, FloatT>>
    FloatingPoint& operator-=(TypeT) = delete;

    template <typename TypeT,
              typename = detail::enable_safe_floating_point_conversion<TypeT, FloatT>>
    PHI_ALWAYS_INLINE FloatingPoint& operator*=(const FloatingPoint<TypeT>& other) noexcept
    {
        m_Value *= static_cast<TypeT>(other);
        return *this;
    }

    template <typename TypeT,
              typename = detail::enable_safe_floating_point_conversion<TypeT, FloatT>>
    PHI_ALWAYS_INLINE FloatingPoint& operator*=(const TypeT& other) noexcept
    {
        return *this *= FloatingPoint<TypeT>(other);
    }

    template <typename TypeT,
              typename = detail::fallback_safe_floating_point_conversion<TypeT, FloatT>>
    FloatingPoint& operator*=(FloatingPoint<TypeT>) = delete;

    template <typename TypeT,
              typename = detail::fallback_safe_floating_point_conversion<TypeT, FloatT>>
    FloatingPoint& operator*=(TypeT) = delete;

    template <typename TypeT,
              typename = detail::enable_safe_floating_point_conversion<TypeT, FloatT>>
    PHI_ALWAYS_INLINE FloatingPoint& operator/=(const FloatingPoint<TypeT>& other) noexcept
    {
        m_Value /= static_cast<TypeT>(other);
        return *this;
    }

    template <typename TypeT,
              typename = detail::enable_safe_floating_point_conversion<TypeT, FloatT>>
    PHI_ALWAYS_INLINE FloatingPoint& operator/=(const TypeT& other) noexcept
    {
        return *this /= FloatingPoint<TypeT>(other);
    }

    template <typename TypeT,
              typename = detail::fallback_safe_floating_point_conversion<TypeT, FloatT>>
    FloatingPoint& operator/=(FloatingPoint<TypeT>) = delete;

    template <typename TypeT,
              typename = detail::fallback_safe_floating_point_conversion<TypeT, FloatT>>
    FloatingPoint& operator/=(TypeT) = delete;

    template <typename TypeT,
              typename = detail::enable_safe_floating_point_conversion<TypeT, FloatT>>
    PHI_ALWAYS_INLINE FloatingPoint& operator%=(const FloatingPoint<TypeT>& other) noexcept
    {
        m_Value = std::fmod(m_Value, static_cast<TypeT>(other));
        return *this;
    }

    template <typename TypeT,
              typename = detail::enable_safe_floating_point_conversion<TypeT, FloatT>>
    PHI_ALWAYS_INLINE FloatingPoint& operator%=(const TypeT& other) noexcept
    {
        return *this %= FloatingPoint<TypeT>(other);
    }

    template <typename TypeT,
              typename = detail::fallback_safe_floating_point_conversion<TypeT, FloatT>>
    FloatingPoint& operator%=(FloatingPoint<TypeT>) = delete;

    template <typename TypeT,
              typename = detail::fallback_safe_floating_point_conversion<TypeT, FloatT>>
    FloatingPoint& operator%=(TypeT) = delete;

private:
    FloatT m_Value; /// Wraped float value
};

//=== comparison ===//

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_floating_point_comparison<LhsT, RhsT>>
PHI_ALWAYS_INLINE constexpr Boolean operator<(const FloatingPoint<LhsT>& lhs,
                                              const FloatingPoint<RhsT>& rhs) noexcept
{
    return static_cast<LhsT>(lhs) < static_cast<RhsT>(rhs);
}

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_floating_point_conversion<LhsT, RhsT>>
PHI_ALWAYS_INLINE constexpr Boolean operator<(const LhsT&                lhs,
                                              const FloatingPoint<RhsT>& rhs) noexcept
{
    return FloatingPoint<LhsT>(lhs) < rhs;
}

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_floating_point_comparison<LhsT, RhsT>>
PHI_ALWAYS_INLINE constexpr Boolean operator<(const FloatingPoint<LhsT>& lhs,
                                              const RhsT&                rhs) noexcept
{
    return lhs < FloatingPoint<RhsT>(rhs);
}

template <typename LhsT, typename RhsT,
          typename = detail::fallback_safe_floating_point_comparison<LhsT, RhsT>>
constexpr Boolean operator<(FloatingPoint<LhsT>, FloatingPoint<RhsT>) = delete;

template <typename LhsT, typename RhsT,
          typename = detail::fallback_safe_floating_point_comparison<LhsT, RhsT>>
constexpr Boolean operator<(LhsT, FloatingPoint<RhsT>) = delete;

template <typename LhsT, typename RhsT,
          typename = detail::fallback_safe_floating_point_comparison<LhsT, RhsT>>
constexpr Boolean operator<(FloatingPoint<LhsT>, RhsT) = delete;

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_floating_point_comparison<LhsT, RhsT>>
PHI_ALWAYS_INLINE constexpr Boolean operator<=(const FloatingPoint<LhsT>& lhs,
                                               const FloatingPoint<RhsT>& rhs) noexcept
{
    return static_cast<LhsT>(lhs) <= static_cast<RhsT>(rhs);
}

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_floating_point_conversion<LhsT, RhsT>>
PHI_ALWAYS_INLINE constexpr Boolean operator<=(const LhsT&                lhs,
                                               const FloatingPoint<RhsT>& rhs) noexcept
{
    return FloatingPoint<LhsT>(lhs) <= rhs;
}

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_floating_point_comparison<LhsT, RhsT>>
PHI_ALWAYS_INLINE constexpr Boolean operator<=(const FloatingPoint<LhsT>& lhs,
                                               const RhsT&                rhs) noexcept
{
    return lhs <= FloatingPoint<RhsT>(rhs);
}

template <typename LhsT, typename RhsT,
          typename = detail::fallback_safe_floating_point_comparison<LhsT, RhsT>>
constexpr Boolean operator<=(FloatingPoint<LhsT>, FloatingPoint<RhsT>) = delete;

template <typename LhsT, typename RhsT,
          typename = detail::fallback_safe_floating_point_comparison<LhsT, RhsT>>
constexpr Boolean operator<=(LhsT, FloatingPoint<RhsT>) = delete;

template <typename LhsT, typename RhsT,
          typename = detail::fallback_safe_floating_point_comparison<LhsT, RhsT>>
constexpr Boolean operator<=(FloatingPoint<LhsT>, RhsT) = delete;

PHI_CLANG_SUPPRESS_WARNING_PUSH()
PHI_CLANG_SUPPRESS_WARNING("-Wdouble-promotion")

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_floating_point_comparison<LhsT, RhsT>>
PHI_ALWAYS_INLINE constexpr Boolean operator>(const FloatingPoint<LhsT>& lhs,
                                              const FloatingPoint<RhsT>& rhs) noexcept
{
    return static_cast<LhsT>(lhs) > static_cast<RhsT>(rhs);
}

PHI_CLANG_SUPPRESS_WARNING_POP()

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_floating_point_conversion<LhsT, RhsT>>
PHI_ALWAYS_INLINE constexpr Boolean operator>(const LhsT&                lhs,
                                              const FloatingPoint<RhsT>& rhs) noexcept
{
    return FloatingPoint<LhsT>(lhs) > rhs;
}

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_floating_point_comparison<LhsT, RhsT>>
PHI_ALWAYS_INLINE constexpr Boolean operator>(const FloatingPoint<LhsT>& lhs,
                                              const RhsT&                rhs) noexcept
{
    return lhs > FloatingPoint<RhsT>(rhs);
}

template <typename LhsT, typename RhsT,
          typename = detail::fallback_safe_floating_point_comparison<LhsT, RhsT>>
constexpr Boolean operator>(FloatingPoint<LhsT>, FloatingPoint<RhsT>) = delete;

template <typename LhsT, typename RhsT,
          typename = detail::fallback_safe_floating_point_comparison<LhsT, RhsT>>
constexpr Boolean operator>(LhsT, FloatingPoint<RhsT>) = delete;

template <typename LhsT, typename RhsT,
          typename = detail::fallback_safe_floating_point_comparison<LhsT, RhsT>>
constexpr Boolean operator>(FloatingPoint<LhsT>, RhsT) = delete;

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_floating_point_comparison<LhsT, RhsT>>
PHI_ALWAYS_INLINE constexpr Boolean operator>=(const FloatingPoint<LhsT>& lhs,
                                               const FloatingPoint<RhsT>& rhs) noexcept
{
    return static_cast<LhsT>(lhs) >= static_cast<RhsT>(rhs);
}

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_floating_point_conversion<LhsT, RhsT>>
PHI_ALWAYS_INLINE constexpr Boolean operator>=(const LhsT&                lhs,
                                               const FloatingPoint<RhsT>& rhs) noexcept
{
    return FloatingPoint<LhsT>(lhs) >= rhs;
}

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_floating_point_comparison<LhsT, RhsT>>
PHI_ALWAYS_INLINE constexpr Boolean operator>=(const FloatingPoint<LhsT>& lhs,
                                               const RhsT&                rhs) noexcept
{
    return lhs >= FloatingPoint<RhsT>(rhs);
}

template <typename LhsT, typename RhsT,
          typename = detail::fallback_safe_floating_point_comparison<LhsT, RhsT>>
constexpr Boolean operator>=(FloatingPoint<LhsT>, FloatingPoint<RhsT>) = delete;

template <typename LhsT, typename RhsT,
          typename = detail::fallback_safe_floating_point_comparison<LhsT, RhsT>>
constexpr Boolean operator>=(LhsT, FloatingPoint<RhsT>) = delete;

template <typename LhsT, typename RhsT,
          typename = detail::fallback_safe_floating_point_comparison<LhsT, RhsT>>
constexpr Boolean operator>=(FloatingPoint<LhsT>, RhsT) = delete;

//=== binary operations ===//

template <typename LhsT, typename RhsT>
PHI_ALWAYS_INLINE constexpr auto operator+(const FloatingPoint<LhsT>& lhs,
                                           const FloatingPoint<RhsT>& rhs) noexcept
        -> detail::floating_point_result_t<LhsT, RhsT>
{
    return static_cast<LhsT>(lhs) + static_cast<RhsT>(rhs);
}

template <typename LhsT, typename RhsT>
PHI_ALWAYS_INLINE constexpr auto operator+(const LhsT& lhs, const FloatingPoint<RhsT>& rhs) noexcept
        -> detail::floating_point_result_t<LhsT, RhsT>
{
    return FloatingPoint<LhsT>(lhs) + rhs;
}

template <typename LhsT, typename RhsT>
PHI_ALWAYS_INLINE constexpr auto operator+(const FloatingPoint<LhsT>& lhs, const RhsT& rhs) noexcept
        -> detail::floating_point_result_t<LhsT, RhsT>
{
    return lhs + FloatingPoint<RhsT>(rhs);
}

template <typename LhsT, typename RhsT>
PHI_ALWAYS_INLINE constexpr auto operator-(const FloatingPoint<LhsT>& lhs,
                                           const FloatingPoint<RhsT>& rhs) noexcept
        -> detail::floating_point_result_t<LhsT, RhsT>
{
    return static_cast<LhsT>(lhs) - static_cast<RhsT>(rhs);
}

template <typename LhsT, typename RhsT>
PHI_ALWAYS_INLINE constexpr auto operator-(const LhsT& lhs, const FloatingPoint<RhsT>& rhs) noexcept
        -> detail::floating_point_result_t<LhsT, RhsT>
{
    return FloatingPoint<LhsT>(lhs) - rhs;
}

template <typename LhsT, typename RhsT>
PHI_ALWAYS_INLINE constexpr auto operator-(const FloatingPoint<LhsT>& lhs, const RhsT& rhs) noexcept
        -> detail::floating_point_result_t<LhsT, RhsT>
{
    return lhs - FloatingPoint<RhsT>(rhs);
}

template <typename LhsT, typename RhsT>
PHI_ALWAYS_INLINE constexpr auto operator*(const FloatingPoint<LhsT>& lhs,
                                           const FloatingPoint<RhsT>& rhs) noexcept
        -> detail::floating_point_result_t<LhsT, RhsT>
{
    return static_cast<LhsT>(lhs) * static_cast<RhsT>(rhs);
}

template <typename LhsT, typename RhsT>
PHI_ALWAYS_INLINE constexpr auto operator*(const LhsT& lhs, const FloatingPoint<RhsT>& rhs) noexcept
        -> detail::floating_point_result_t<LhsT, RhsT>
{
    return FloatingPoint<LhsT>(lhs) * rhs;
}

template <typename LhsT, typename RhsT>
PHI_ALWAYS_INLINE constexpr auto operator*(const FloatingPoint<LhsT>& lhs, const RhsT& rhs) noexcept
        -> detail::floating_point_result_t<LhsT, RhsT>
{
    return lhs * FloatingPoint<RhsT>(rhs);
}

template <typename LhsT, typename RhsT>
PHI_ALWAYS_INLINE constexpr auto operator/(const FloatingPoint<LhsT>& lhs,
                                           const FloatingPoint<RhsT>& rhs) noexcept
        -> detail::floating_point_result_t<LhsT, RhsT>
{
    return static_cast<LhsT>(lhs) / static_cast<RhsT>(rhs);
}

template <typename LhsT, typename RhsT>
PHI_ALWAYS_INLINE constexpr auto operator/(const LhsT& lhs, const FloatingPoint<RhsT>& rhs) noexcept
        -> detail::floating_point_result_t<LhsT, RhsT>
{
    return FloatingPoint<LhsT>(lhs) / rhs;
}

template <typename LhsT, typename RhsT>
PHI_ALWAYS_INLINE constexpr auto operator/(const FloatingPoint<LhsT>& lhs, const RhsT& rhs) noexcept
        -> detail::floating_point_result_t<LhsT, RhsT>
{
    return lhs / FloatingPoint<RhsT>(rhs);
}

template <typename LhsT, typename RhsT>
PHI_ALWAYS_INLINE constexpr auto operator%(const FloatingPoint<LhsT>& lhs,
                                           const FloatingPoint<RhsT>& rhs) noexcept
        -> detail::floating_point_result_t<LhsT, RhsT>
{
    return std::fmod(static_cast<LhsT>(lhs), static_cast<RhsT>(rhs));
}

template <typename LhsT, typename RhsT>
PHI_ALWAYS_INLINE constexpr auto operator%(const LhsT& lhs, const FloatingPoint<RhsT>& rhs) noexcept
        -> detail::floating_point_result_t<LhsT, RhsT>
{
    return FloatingPoint<LhsT>(lhs) % rhs;
}

template <typename LhsT, typename RhsT>
PHI_ALWAYS_INLINE constexpr auto operator%(const FloatingPoint<LhsT>& lhs, const RhsT& rhs) noexcept
        -> detail::floating_point_result_t<LhsT, RhsT>
{
    return lhs % FloatingPoint<RhsT>(rhs);
}

//=== input/output ===/

template <typename CharT, class CharTraitsT, typename FloatT>
std::basic_istream<CharT, CharTraitsT>& operator>>(std::basic_istream<CharT, CharTraitsT>& in,
                                                   FloatingPoint<FloatT>&                  f)
{
    FloatT val{FloatT(0.0)};
    in >> val;
    f = val;
    return in;
}

template <typename CharT, class CharTraitsT, typename FloatT>
std::basic_ostream<CharT, CharTraitsT>& operator<<(std::basic_ostream<CharT, CharTraitsT>& out,
                                                   const FloatingPoint<FloatT>&            f)
{
    return out << static_cast<FloatT>(f);
}

DETAIL_PHI_END_NAMESPACE()

namespace std
{
    template <typename FloatT>
    struct hash<phi::FloatingPoint<FloatT>>
    {
        std::size_t operator()(const phi::FloatingPoint<FloatT>& value) const noexcept
        {
            return std::hash<FloatT>()(static_cast<FloatT>(value));
        }
    };

    template <typename FloatT>
    struct numeric_limits<phi::FloatingPoint<FloatT>> : std::numeric_limits<FloatT>
    {};
} // namespace std

#endif // INCG_PHI_UTILITY_FLOATINGPOINT_HPP
