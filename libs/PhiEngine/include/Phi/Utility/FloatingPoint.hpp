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
#include <cpp/Inline.hpp>
#include <functional>
#include <iosfwd>
#include <type_traits>

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename FloatT>
class FloatingPoint;

/// \cond detail
namespace detail
{
    template <typename FromT, typename ToT>
    struct is_safe_floating_point_conversion
        : std::bool_constant<std::is_floating_point_v<FromT> && std::is_floating_point_v<ToT> &&
                             sizeof(FromT) <= sizeof(ToT)>
    {};

    template <typename FromT, typename ToT>
    constexpr inline bool IsSafeFloatingPointConversionV =
            is_safe_floating_point_conversion<FromT, ToT>::value;

    template <typename FromT, typename ToT>
    using enable_safe_floating_point_conversion =
            typename std::enable_if_t<IsSafeFloatingPointConversionV<FromT, ToT>>;

    template <typename FromT, typename ToT>
    using fallback_safe_floating_point_conversion =
            typename std::enable_if_t<!IsSafeFloatingPointConversionV<FromT, ToT>>;

    template <typename LhsT, typename RhsT>
    struct is_safe_floating_point_comparison
        : std::bool_constant<IsSafeFloatingPointConversionV<LhsT, RhsT> ||
                             IsSafeFloatingPointConversionV<RhsT, LhsT>>
    {};

    template <typename LhsT, typename RhsT>
    constexpr inline bool IsSafeFloatingPointComparisonV =
            is_safe_floating_point_comparison<LhsT, RhsT>::value;

    template <typename LhsT, typename RhsT>
    using enable_safe_floating_point_comparison =
            typename std::enable_if_t<IsSafeFloatingPointComparisonV<LhsT, RhsT>>;

    template <typename LhsT, typename RhsT>
    using fallback_safe_floating_point_comparison =
            typename std::enable_if_t<!IsSafeFloatingPointComparisonV<LhsT, RhsT>>;

    template <typename LhsT, typename RhsT>
    struct is_safe_floating_point_operation
        : std::bool_constant<std::is_floating_point_v<LhsT> && std::is_floating_point_v<RhsT>>
    {};

    template <typename LhsT, typename RhsT>
    constexpr inline bool IsSafeFloatingPointOperationV =
            is_safe_floating_point_operation<LhsT, RhsT>::value;

    template <typename LhsT, typename RhsT>
    using floating_point_result_t = FloatingPoint<typename std::enable_if_t<
            IsSafeFloatingPointOperationV<LhsT, RhsT>,
            typename std::conditional_t<sizeof(LhsT) < sizeof(RhsT), RhsT, LhsT>>>;

    template <typename LhsT, typename RhsT>
    using fallback_floating_point_result =
            typename std::enable_if_t<!IsSafeFloatingPointOperationV<LhsT, RhsT>>;
} // namespace detail
/// \endcond

template <typename FloatT>
class FloatingPoint
{
    static_assert(std::is_floating_point_v<FloatT>, "must be a floating point type");

public:
    using value_type = FloatT;

    FloatingPoint() = delete;

    template <typename TypeT,
              typename = detail::enable_safe_floating_point_conversion<TypeT, FloatT>>
    CPP_ALWAYS_INLINE constexpr FloatingPoint(const TypeT& val) noexcept
        : m_Value(val)
    {}

    template <typename TypeT,
              typename = detail::enable_safe_floating_point_conversion<TypeT, FloatT>>
    CPP_ALWAYS_INLINE constexpr FloatingPoint(const FloatingPoint<TypeT>& val) noexcept
        : m_Value(static_cast<TypeT>(val))
    {}

    template <typename TypeT,
              typename = detail::fallback_safe_floating_point_conversion<TypeT, FloatT>>
    constexpr FloatingPoint(TypeT) = delete;

    //=== assignment ===//
    template <typename TypeT,
              typename = detail::enable_safe_floating_point_conversion<TypeT, FloatT>>
    CPP_ALWAYS_INLINE FloatingPoint& operator=(const TypeT& val) noexcept
    {
        m_Value = val;
        return *this;
    }

    template <typename TypeT,
              typename = detail::enable_safe_floating_point_conversion<TypeT, FloatT>>
    CPP_ALWAYS_INLINE FloatingPoint& operator=(const FloatingPoint<TypeT>& val) noexcept
    {
        m_Value = static_cast<TypeT>(val);
        return *this;
    }

    template <typename TypeT,
              typename = detail::fallback_safe_floating_point_conversion<TypeT, FloatT>>
    FloatingPoint& operator=(TypeT) = delete;

    //=== conversion back ===//
    CPP_ALWAYS_INLINE explicit constexpr operator FloatT() const noexcept
    {
        return m_Value;
    }

    CPP_ALWAYS_INLINE constexpr FloatT get() const noexcept
    {
        return m_Value;
    }

    //=== unary operators ===//
    CPP_ALWAYS_INLINE constexpr FloatingPoint operator+() const noexcept
    {
        return *this;
    }

    CPP_ALWAYS_INLINE constexpr FloatingPoint operator-() const noexcept
    {
        return -m_Value;
    }

//=== compound assignment ====//
#define DETAIL_PHI_MAKE_OP(Op)                                                                     \
                                                                                                   \
    template <typename T, typename = detail::enable_safe_floating_point_conversion<T, FloatT>>     \
    CPP_ALWAYS_INLINE FloatingPoint& operator Op(const T& other) noexcept                          \
    {                                                                                              \
        return *this Op FloatingPoint<T>(other);                                                   \
    }                                                                                              \
                                                                                                   \
    template <typename T, typename = detail::fallback_safe_floating_point_conversion<T, FloatT>>   \
    FloatingPoint& operator Op(FloatingPoint<T>) = delete;                                         \
                                                                                                   \
    template <typename T, typename = detail::fallback_safe_floating_point_conversion<T, FloatT>>   \
    FloatingPoint& operator Op(T) = delete;

    template <typename TypeT,
              typename = detail::enable_safe_floating_point_conversion<TypeT, FloatT>>
    CPP_ALWAYS_INLINE FloatingPoint& operator+=(const FloatingPoint<TypeT>& other) noexcept
    {
        m_Value += static_cast<TypeT>(other);
        return *this;
    }
    DETAIL_PHI_MAKE_OP(+=)

    template <typename TypeT,
              typename = detail::enable_safe_floating_point_conversion<TypeT, FloatT>>
    CPP_ALWAYS_INLINE FloatingPoint& operator-=(const FloatingPoint<TypeT>& other) noexcept
    {
        m_Value -= static_cast<TypeT>(other);
        return *this;
    }
    DETAIL_PHI_MAKE_OP(-=)

    template <typename TypeT,
              typename = detail::enable_safe_floating_point_conversion<TypeT, FloatT>>
    CPP_ALWAYS_INLINE FloatingPoint& operator*=(const FloatingPoint<TypeT>& other) noexcept
    {
        m_Value *= static_cast<TypeT>(other);
        return *this;
    }
    DETAIL_PHI_MAKE_OP(*=)

    template <typename TypeT,
              typename = detail::enable_safe_floating_point_conversion<TypeT, FloatT>>
    CPP_ALWAYS_INLINE FloatingPoint& operator/=(const FloatingPoint<TypeT>& other) noexcept
    {
        m_Value /= static_cast<TypeT>(other);
        return *this;
    }
    DETAIL_PHI_MAKE_OP(/=)

#undef DETAIL_PHI_MAKE_OP

private:
    FloatT m_Value; /// Wraped float value
};

//=== comparison ===//
#define DETAIL_PHI_MAKE_OP(Op)                                                                     \
                                                                                                   \
    template <typename LhsT, typename RhsT,                                                        \
              typename = detail::enable_safe_floating_point_conversion<LhsT, RhsT>>                \
    CPP_ALWAYS_INLINE constexpr bool operator Op(const LhsT& lhs, const FloatingPoint<RhsT>& rhs)  \
    {                                                                                              \
        return FloatingPoint<LhsT>(lhs) Op rhs;                                                    \
    }                                                                                              \
                                                                                                   \
    template <typename LhsT, typename RhsT,                                                        \
              typename = detail::enable_safe_floating_point_comparison<LhsT, RhsT>>                \
    CPP_ALWAYS_INLINE constexpr bool operator Op(const FloatingPoint<LhsT>& lhs, const RhsT& rhs)  \
    {                                                                                              \
        return lhs Op FloatingPoint<RhsT>(rhs);                                                    \
    }                                                                                              \
                                                                                                   \
    template <typename LhsT, typename RhsT,                                                        \
              typename = detail::fallback_safe_floating_point_comparison<LhsT, RhsT>>              \
    constexpr bool operator Op(FloatingPoint<LhsT>, FloatingPoint<RhsT>) = delete;                 \
                                                                                                   \
    template <typename LhsT, typename RhsT,                                                        \
              typename = detail::fallback_safe_floating_point_comparison<LhsT, RhsT>>              \
    constexpr bool operator Op(LhsT, FloatingPoint<RhsT>) = delete;                                \
                                                                                                   \
    template <typename LhsT, typename RhsT,                                                        \
              typename = detail::fallback_safe_floating_point_comparison<LhsT, RhsT>>              \
    constexpr bool operator Op(FloatingPoint<LhsT>, RhsT) = delete;

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_floating_point_comparison<LhsT, RhsT>>
CPP_ALWAYS_INLINE constexpr bool operator<(const FloatingPoint<LhsT>& lhs,
                                           const FloatingPoint<RhsT>& rhs) noexcept
{
    return static_cast<LhsT>(lhs) < static_cast<RhsT>(rhs);
}
DETAIL_PHI_MAKE_OP(<)

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_floating_point_comparison<LhsT, RhsT>>
CPP_ALWAYS_INLINE constexpr bool operator<=(const FloatingPoint<LhsT>& lhs,
                                            const FloatingPoint<RhsT>& rhs) noexcept
{
    return static_cast<LhsT>(lhs) <= static_cast<RhsT>(rhs);
}
DETAIL_PHI_MAKE_OP(<=)

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_floating_point_comparison<LhsT, RhsT>>
CPP_ALWAYS_INLINE constexpr bool operator>(const FloatingPoint<LhsT>& lhs,
                                           const FloatingPoint<RhsT>& rhs) noexcept
{
    return static_cast<LhsT>(lhs) > static_cast<RhsT>(rhs);
}
DETAIL_PHI_MAKE_OP(>)

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_floating_point_comparison<LhsT, RhsT>>
CPP_ALWAYS_INLINE constexpr bool operator>=(const FloatingPoint<LhsT>& lhs,
                                            const FloatingPoint<RhsT>& rhs) noexcept
{
    return static_cast<LhsT>(lhs) >= static_cast<RhsT>(rhs);
}
DETAIL_PHI_MAKE_OP(>=)

#undef DETAIL_PHI_MAKE_OP

//=== binary operations ===//
#define DETAIL_PHI_MAKE_OP(Op)                                                                     \
    template <typename LhsT, typename RhsT>                                                        \
    CPP_ALWAYS_INLINE constexpr auto operator Op(                                                  \
            const LhsT&                lhs,                                                        \
            const FloatingPoint<RhsT>& rhs) noexcept->detail::floating_point_result_t<LhsT, RhsT>  \
    {                                                                                              \
        return FloatingPoint<LhsT>(lhs) Op rhs;                                                    \
    }                                                                                              \
                                                                                                   \
    template <typename LhsT, typename RhsT>                                                        \
    CPP_ALWAYS_INLINE constexpr auto operator Op(                                                  \
            const FloatingPoint<LhsT>& lhs,                                                        \
            const RhsT&                rhs) noexcept->detail::floating_point_result_t<LhsT, RhsT>                 \
    {                                                                                              \
        return lhs Op FloatingPoint<RhsT>(rhs);                                                    \
    }                                                                                              \
                                                                                                   \
    template <typename LhsT, typename RhsT,                                                        \
              typename = detail::fallback_floating_point_result<LhsT, RhsT>>                       \
    constexpr int operator Op(FloatingPoint<LhsT>, FloatingPoint<RhsT>) noexcept = delete;         \
                                                                                                   \
    template <typename LhsT, typename RhsT,                                                        \
              typename = detail::fallback_floating_point_result<LhsT, RhsT>>                       \
    constexpr int operator Op(LhsT, FloatingPoint<RhsT>) noexcept = delete;                        \
                                                                                                   \
    template <typename LhsT, typename RhsT,                                                        \
              typename = detail::fallback_floating_point_result<LhsT, RhsT>>                       \
    constexpr int operator Op(FloatingPoint<LhsT>, RhsT) noexcept = delete;

template <typename LhsT, typename RhsT>
CPP_ALWAYS_INLINE constexpr auto operator+(const FloatingPoint<LhsT>& lhs,
                                           const FloatingPoint<RhsT>& rhs) noexcept
        -> detail::floating_point_result_t<LhsT, RhsT>
{
    return static_cast<LhsT>(lhs) + static_cast<RhsT>(rhs);
}
DETAIL_PHI_MAKE_OP(+)

template <typename LhsT, typename RhsT>
CPP_ALWAYS_INLINE constexpr auto operator-(const FloatingPoint<LhsT>& lhs,
                                           const FloatingPoint<RhsT>& rhs) noexcept
        -> detail::floating_point_result_t<LhsT, RhsT>
{
    return static_cast<LhsT>(lhs) - static_cast<RhsT>(rhs);
}
DETAIL_PHI_MAKE_OP(-)

template <typename LhsT, typename RhsT>
CPP_ALWAYS_INLINE constexpr auto operator*(const FloatingPoint<LhsT>& lhs,
                                           const FloatingPoint<RhsT>& rhs) noexcept
        -> detail::floating_point_result_t<LhsT, RhsT>
{
    return static_cast<LhsT>(lhs) * static_cast<RhsT>(rhs);
}
DETAIL_PHI_MAKE_OP(*)

template <typename LhsT, typename RhsT>
CPP_ALWAYS_INLINE constexpr auto operator/(const FloatingPoint<LhsT>& lhs,
                                           const FloatingPoint<RhsT>& rhs) noexcept
        -> detail::floating_point_result_t<LhsT, RhsT>
{
    return static_cast<LhsT>(lhs) / static_cast<RhsT>(rhs);
}
DETAIL_PHI_MAKE_OP(/)

#undef DETAIL_PHI_MAKE_OP

//=== input/output ===/
template <typename CharT, class CharTraitsT, typename FloatT>
std::basic_istream<CharT, CharTraitsT>& operator>>(std::basic_istream<CharT, CharTraitsT>& in,
                                                   FloatingPoint<FloatT>&                  f)
{
    FloatT val;
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
} // namespace std

#endif // INCG_PHI_UTILITY_FLOATINGPOINT_HPP
