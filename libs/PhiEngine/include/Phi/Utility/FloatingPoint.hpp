// This file is heavily inspired by Jonathan Müllers <jonathanmueller.dev@gmail.com> type_safe library https://github.com/foonathan/type_safe
// licensed under the MIT license https://github.com/foonathan/type_safe/blob/master/LICENSE
// Original file at https://github.com/foonathan/type_safe/blob/master/include/type_safe/FloatingPoint.hpp
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
    template <typename From, typename To>
    struct is_safe_floating_point_conversion
        : std::bool_constant<std::is_floating_point_v<From> && std::is_floating_point_v<To> &&
                             sizeof(From) <= sizeof(To)>
    {};

    template <typename From, typename To>
    constexpr inline bool is_safe_floating_point_conversion_v =
            is_safe_floating_point_conversion<From, To>::value;

    template <typename From, typename To>
    using enable_safe_floating_point_conversion =
            typename std::enable_if_t<is_safe_floating_point_conversion_v<From, To>>;

    template <typename From, typename To>
    using fallback_safe_floating_point_conversion =
            typename std::enable_if_t<!is_safe_floating_point_conversion_v<From, To>>;

    template <typename Lhs, typename Rhs>
    struct is_safe_floating_point_comparison
        : std::bool_constant<is_safe_floating_point_conversion_v<Lhs, Rhs> ||
                             is_safe_floating_point_conversion_v<Rhs, Lhs>>
    {};

    template <typename Lhs, typename Rhs>
    constexpr inline bool is_safe_floating_point_comparison_v =
            is_safe_floating_point_comparison<Lhs, Rhs>::value;

    template <typename Lhs, typename Rhs>
    using enable_safe_floating_point_comparison =
            typename std::enable_if_t<is_safe_floating_point_comparison_v<Lhs, Rhs>>;

    template <typename Lhs, typename Rhs>
    using fallback_safe_floating_point_comparison =
            typename std::enable_if_t<!is_safe_floating_point_comparison_v<Lhs, Rhs>>;

    template <typename Lhs, typename Rhs>
    struct is_safe_floating_point_operation
        : std::bool_constant<std::is_floating_point_v<Lhs> && std::is_floating_point_v<Rhs>>
    {};

    template <typename Lhs, typename Rhs>
    constexpr inline bool is_safe_floating_point_operation_v =
            is_safe_floating_point_operation<Lhs, Rhs>::value;

    template <typename Lhs, typename Rhs>
    using floating_point_result_t = FloatingPoint<typename std::enable_if_t<
            is_safe_floating_point_operation_v<Lhs, Rhs>,
            typename std::conditional_t<sizeof(Lhs) < sizeof(Rhs), Rhs, Lhs>>>;

    template <typename Lhs, typename Rhs>
    using fallback_floating_point_result =
            typename std::enable_if_t<!is_safe_floating_point_operation_v<Lhs, Rhs>>;
} // namespace detail
/// \endcond

template <typename FloatT>
class FloatingPoint
{
    static_assert(std::is_floating_point_v<FloatT>, "must be a floating point type");

public:
    using value_type = FloatT;

    FloatingPoint() = delete;

    template <typename T, typename = detail::enable_safe_floating_point_conversion<T, FloatT>>
    CPP_ALWAYS_INLINE constexpr FloatingPoint(const T& val) noexcept
        : m_Value(val)
    {}

    template <typename T, typename = detail::enable_safe_floating_point_conversion<T, FloatT>>
    CPP_ALWAYS_INLINE constexpr FloatingPoint(const FloatingPoint<T>& val) noexcept
        : m_Value(static_cast<T>(val))
    {}

    template <typename T, typename = detail::fallback_safe_floating_point_conversion<T, FloatT>>
    constexpr FloatingPoint(T) = delete;

    //=== assignment ===//
    template <typename T, typename = detail::enable_safe_floating_point_conversion<T, FloatT>>
    CPP_ALWAYS_INLINE FloatingPoint& operator=(const T& val) noexcept
    {
        m_Value = val;
        return *this;
    }

    template <typename T, typename = detail::enable_safe_floating_point_conversion<T, FloatT>>
    CPP_ALWAYS_INLINE FloatingPoint& operator=(const FloatingPoint<T>& val) noexcept
    {
        m_Value = static_cast<T>(val);
        return *this;
    }

    template <typename T, typename = detail::fallback_safe_floating_point_conversion<T, FloatT>>
    FloatingPoint& operator=(T) = delete;

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

    template <typename T, typename = detail::enable_safe_floating_point_conversion<T, FloatT>>
    CPP_ALWAYS_INLINE FloatingPoint& operator+=(const FloatingPoint<T>& other) noexcept
    {
        m_Value += static_cast<T>(other);
        return *this;
    }
    DETAIL_PHI_MAKE_OP(+=)

    template <typename T, typename = detail::enable_safe_floating_point_conversion<T, FloatT>>
    CPP_ALWAYS_INLINE FloatingPoint& operator-=(const FloatingPoint<T>& other) noexcept
    {
        m_Value -= static_cast<T>(other);
        return *this;
    }
    DETAIL_PHI_MAKE_OP(-=)

    template <typename T, typename = detail::enable_safe_floating_point_conversion<T, FloatT>>
    CPP_ALWAYS_INLINE FloatingPoint& operator*=(const FloatingPoint<T>& other) noexcept
    {
        m_Value *= static_cast<T>(other);
        return *this;
    }
    DETAIL_PHI_MAKE_OP(*=)

    template <typename T, typename = detail::enable_safe_floating_point_conversion<T, FloatT>>
    CPP_ALWAYS_INLINE FloatingPoint& operator/=(const FloatingPoint<T>& other) noexcept
    {
        m_Value /= static_cast<T>(other);
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
    template <typename A, typename B,                                                              \
              typename = detail::enable_safe_floating_point_conversion<A, B>>                      \
    CPP_ALWAYS_INLINE constexpr bool operator Op(const A& a, const FloatingPoint<B>& b)            \
    {                                                                                              \
        return FloatingPoint<A>(a) Op b;                                                           \
    }                                                                                              \
                                                                                                   \
    template <typename A, typename B,                                                              \
              typename = detail::enable_safe_floating_point_comparison<A, B>>                      \
    CPP_ALWAYS_INLINE constexpr bool operator Op(const FloatingPoint<A>& a, const B& b)            \
    {                                                                                              \
        return a Op FloatingPoint<B>(b);                                                           \
    }                                                                                              \
                                                                                                   \
    template <typename A, typename B,                                                              \
              typename = detail::fallback_safe_floating_point_comparison<A, B>>                    \
    constexpr bool operator Op(FloatingPoint<A>, FloatingPoint<B>) = delete;                       \
                                                                                                   \
    template <typename A, typename B,                                                              \
              typename = detail::fallback_safe_floating_point_comparison<A, B>>                    \
    constexpr bool operator Op(A, FloatingPoint<B>) = delete;                                      \
                                                                                                   \
    template <typename A, typename B,                                                              \
              typename = detail::fallback_safe_floating_point_comparison<A, B>>                    \
    constexpr bool operator Op(FloatingPoint<A>, B) = delete;

template <typename A, typename B, typename = detail::enable_safe_floating_point_comparison<A, B>>
CPP_ALWAYS_INLINE constexpr bool operator<(const FloatingPoint<A>& a,
                                           const FloatingPoint<B>& b) noexcept
{
    return static_cast<A>(a) < static_cast<B>(b);
}
DETAIL_PHI_MAKE_OP(<)

template <typename A, typename B, typename = detail::enable_safe_floating_point_comparison<A, B>>
CPP_ALWAYS_INLINE constexpr bool operator<=(const FloatingPoint<A>& a,
                                            const FloatingPoint<B>& b) noexcept
{
    return static_cast<A>(a) <= static_cast<B>(b);
}
DETAIL_PHI_MAKE_OP(<=)

template <typename A, typename B, typename = detail::enable_safe_floating_point_comparison<A, B>>
CPP_ALWAYS_INLINE constexpr bool operator>(const FloatingPoint<A>& a,
                                           const FloatingPoint<B>& b) noexcept
{
    return static_cast<A>(a) > static_cast<B>(b);
}
DETAIL_PHI_MAKE_OP(>)

template <typename A, typename B, typename = detail::enable_safe_floating_point_comparison<A, B>>
CPP_ALWAYS_INLINE constexpr bool operator>=(const FloatingPoint<A>& a,
                                            const FloatingPoint<B>& b) noexcept
{
    return static_cast<A>(a) >= static_cast<B>(b);
}
DETAIL_PHI_MAKE_OP(>=)

#undef DETAIL_PHI_MAKE_OP

//=== binary operations ===//
#define DETAIL_PHI_MAKE_OP(Op)                                                                     \
    template <typename A, typename B>                                                              \
    CPP_ALWAYS_INLINE constexpr auto operator Op(                                                  \
            const A& a, const FloatingPoint<B>& b) noexcept->detail::floating_point_result_t<A, B> \
    {                                                                                              \
        return FloatingPoint<A>(a) Op b;                                                           \
    }                                                                                              \
                                                                                                   \
    template <typename A, typename B>                                                              \
    CPP_ALWAYS_INLINE constexpr auto operator Op(                                                  \
            const FloatingPoint<A>& a, const B& b) noexcept->detail::floating_point_result_t<A, B> \
    {                                                                                              \
        return a Op FloatingPoint<B>(b);                                                           \
    }                                                                                              \
                                                                                                   \
    template <typename A, typename B, typename = detail::fallback_floating_point_result<A, B>>     \
    constexpr int operator Op(FloatingPoint<A>, FloatingPoint<B>) noexcept = delete;               \
                                                                                                   \
    template <typename A, typename B, typename = detail::fallback_floating_point_result<A, B>>     \
    constexpr int operator Op(A, FloatingPoint<B>) noexcept = delete;                              \
                                                                                                   \
    template <typename A, typename B, typename = detail::fallback_floating_point_result<A, B>>     \
    constexpr int operator Op(FloatingPoint<A>, B) noexcept = delete;

template <typename A, typename B>
CPP_ALWAYS_INLINE constexpr auto operator+(const FloatingPoint<A>& a,
                                           const FloatingPoint<B>& b) noexcept
        -> detail::floating_point_result_t<A, B>
{
    return static_cast<A>(a) + static_cast<B>(b);
}
DETAIL_PHI_MAKE_OP(+)

template <typename A, typename B>
CPP_ALWAYS_INLINE constexpr auto operator-(const FloatingPoint<A>& a,
                                           const FloatingPoint<B>& b) noexcept
        -> detail::floating_point_result_t<A, B>
{
    return static_cast<A>(a) - static_cast<B>(b);
}
DETAIL_PHI_MAKE_OP(-)

template <typename A, typename B>
CPP_ALWAYS_INLINE constexpr auto operator*(const FloatingPoint<A>& a,
                                           const FloatingPoint<B>& b) noexcept
        -> detail::floating_point_result_t<A, B>
{
    return static_cast<A>(a) * static_cast<B>(b);
}
DETAIL_PHI_MAKE_OP(*)

template <typename A, typename B>
CPP_ALWAYS_INLINE constexpr auto operator/(const FloatingPoint<A>& a,
                                           const FloatingPoint<B>& b) noexcept
        -> detail::floating_point_result_t<A, B>
{
    return static_cast<A>(a) / static_cast<B>(b);
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
