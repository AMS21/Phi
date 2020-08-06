// This file is heavily inspired by Jonathan Müllers <jonathanmueller.dev@gmail.com> type_safe library https://github.com/foonathan/type_safe
// licensed under the MIT license https://github.com/foonathan/type_safe/blob/master/LICENSE
// Original file at https://github.com/foonathan/type_safe/blob/master/include/type_safe/integer.hpp
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
#ifndef INCG_PHI_UTILITY_INTEGER_HPP
#define INCG_PHI_UTILITY_INTEGER_HPP

#include "Phi/PhiConfig.hpp"
#include <cpp/Inline.hpp>
#include <functional>
#include <iosfwd>
#include <limits>
#include <type_traits>

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename IntegerT>
class Integer;

/// \cond detail
namespace detail
{
    template <typename T>
    struct is_integer : std::bool_constant<std::is_integral_v<T> && !std::is_same_v<T, bool> &&
                                           !std::is_same_v<T, char>>
    {};

    template <typename T>
    constexpr inline bool is_integer_v = is_integer<T>::value;

    template <typename From, typename To>
    struct is_safe_integer_conversion
        : std::bool_constant<
                  detail::is_integer_v<From> && detail::is_integer_v<To> &&
                  ((sizeof(From) <= sizeof(To) && std::is_signed_v<From> == std::is_signed_v<To>) ||
                   (sizeof(From) < sizeof(To) && std::is_unsigned_v<From> && std::is_signed_v<To>))>
    {};

    template <typename From, typename To>
    constexpr inline bool is_safe_integer_conversion_v =
            is_safe_integer_conversion<From, To>::value;

    template <typename From, typename To>
    using enable_safe_integer_conversion =
            typename std::enable_if_t<is_safe_integer_conversion_v<From, To>>;

    template <typename From, typename To>
    using fallback_safe_integer_conversion =
            typename std::enable_if_t<!is_safe_integer_conversion_v<From, To>>;

    template <typename LhsT, typename RhsT>
    struct is_safe_integer_comparison
        : std::bool_constant<is_safe_integer_conversion_v<LhsT, RhsT> ||
                             is_safe_integer_conversion_v<RhsT, LhsT>>
    {};

    template <typename LhsT, typename RhsT>
    constexpr inline bool is_safe_integer_comparison_v =
            is_safe_integer_comparison<LhsT, RhsT>::value;

    template <typename LhsT, typename RhsT>
    using enable_safe_integer_comparison =
            typename std::enable_if_t<is_safe_integer_comparison_v<LhsT, RhsT>>;

    template <typename LhsT, typename RhsT>
    using fallback_safe_integer_comparison =
            typename std::enable_if_t<!is_safe_integer_comparison_v<LhsT, RhsT>>;

    template <typename LhsT, typename RhsT>
    struct is_safe_integer_operation
        : std::bool_constant<detail::is_integer_v<LhsT> && detail::is_integer_v<RhsT> &&
                             std::is_signed_v<LhsT> == std::is_signed_v<RhsT>>
    {};

    template <typename LhsT, typename RhsT>
    constexpr inline bool is_safe_integer_operation_v =
            is_safe_integer_operation<LhsT, RhsT>::value;

    template <typename LhsT, typename RhsT>
    struct integer_result_type
        : std::enable_if<is_safe_integer_operation_v<LhsT, RhsT>,
                         typename std::conditional_t<sizeof(LhsT) < sizeof(RhsT), RhsT, LhsT>>
    {};

    template <typename LhsT, typename RhsT>
    using integer_result_t = typename integer_result_type<LhsT, RhsT>::type;

    template <typename LhsT, typename RhsT>
    using fallback_integer_result =
            typename std::enable_if_t<!is_safe_integer_operation_v<LhsT, RhsT>>;
} // namespace detail
/// \endcond

/// A type safe integer class.
///
/// This is a tiny, no overhead wrapper over a standard integer type.
/// It behaves exactly like the built-in types except that narrowing conversions are not allowed.
/// It also checks against `unsigned` under/overflow in debug mode
/// and marks it as undefined for the optimizer otherwise.
///
/// A conversion is considered safe if both integer types have the same signedness
/// and the size of the value being converted is less than or equal to the destination size.
///
/// \requires `IntegerT` must be an integral type except `bool` and `char` (use `signed
/// char`/`unsigned char`). \notes It intentionally does not provide the bitwise operations. \module
/// types
template <typename IntegerT>
class Integer
{
    static_assert(detail::is_integer_v<IntegerT>, "Must be a real integer type");

public:
    using value_type  = IntegerT;
    using limits_type = std::numeric_limits<IntegerT>;

public:
    //=== constructors ===//
    Integer() = delete;

    template <typename T, typename = detail::enable_safe_integer_conversion<T, IntegerT>>
    CPP_ALWAYS_INLINE constexpr Integer(const T& val) noexcept
        : m_Value(val)
    {}

    template <typename T, typename = detail::enable_safe_integer_conversion<T, IntegerT>>
    CPP_ALWAYS_INLINE constexpr Integer(const Integer<T>& val) noexcept
        : m_Value(static_cast<T>(val))
    {}

    template <typename T, typename = detail::fallback_safe_integer_conversion<T, IntegerT>>
    constexpr Integer(T) = delete;

    //=== assignment ===//
    template <typename T, typename = detail::enable_safe_integer_conversion<T, IntegerT>>
    CPP_ALWAYS_INLINE Integer& operator=(const T& val) noexcept
    {
        m_Value = val;
        return *this;
    }

    template <typename T, typename = detail::enable_safe_integer_conversion<T, IntegerT>>
    CPP_ALWAYS_INLINE Integer& operator=(const Integer<T>& val) noexcept
    {
        m_Value = static_cast<T>(val);
        return *this;
    }

    //=== conversion back ===//
    CPP_ALWAYS_INLINE explicit constexpr operator IntegerT() const noexcept
    {
        return m_Value;
    }

    CPP_ALWAYS_INLINE constexpr IntegerT get() const noexcept
    {
        return m_Value;
    }

    CPP_ALWAYS_INLINE constexpr static Integer<IntegerT> min() noexcept
    {
        return limits_type::min();
    }

    CPP_ALWAYS_INLINE constexpr static Integer<IntegerT> max() noexcept
    {
        return limits_type::max();
    }

    //=== unary operators ===//
    CPP_ALWAYS_INLINE constexpr Integer operator+() const noexcept
    {
        return *this;
    }

    CPP_ALWAYS_INLINE constexpr Integer operator-() const noexcept
    {
        static_assert(std::is_signed_v<IntegerT>, "Cannot call unary minus on unsigned integer");

        return Integer(-m_Value);
    }

    CPP_ALWAYS_INLINE Integer& operator++() noexcept
    {
        m_Value += 1;
        return *this;
    }

    CPP_ALWAYS_INLINE Integer operator++(int) noexcept
    {
        auto res = *this;
        ++*this;
        return res;
    }

    CPP_ALWAYS_INLINE Integer& operator--() noexcept
    {
        m_Value -= 1;
        return *this;
    }

    /// \group decrement
    CPP_ALWAYS_INLINE Integer operator--(int) noexcept
    {
        auto res = *this;
        --*this;
        return res;
    }

//=== compound assignment ====//
#define DETAIL_PHI_MAKE_OP(Op)                                                                     \
    template <typename T, typename = detail::enable_safe_integer_conversion<T, IntegerT>>          \
    CPP_ALWAYS_INLINE Integer& operator Op(const T& other)                                         \
    {                                                                                              \
        return *this Op Integer<T>(other);                                                         \
    }                                                                                              \
                                                                                                   \
    template <typename T, typename = detail::fallback_safe_integer_conversion<T, IntegerT>>        \
    Integer& operator Op(Integer<T>) = delete;                                                     \
                                                                                                   \
    template <typename T, typename = detail::fallback_safe_integer_conversion<T, IntegerT>>        \
    Integer& operator Op(T) = delete;

    template <typename T, typename = detail::enable_safe_integer_conversion<T, IntegerT>>
    CPP_ALWAYS_INLINE Integer& operator+=(const Integer<T>& other)
    {
        m_Value += other.get();
        return *this;
    }
    DETAIL_PHI_MAKE_OP(+=)

    template <typename T, typename = detail::enable_safe_integer_conversion<T, IntegerT>>
    CPP_ALWAYS_INLINE Integer& operator-=(const Integer<T>& other)
    {
        m_Value -= other.get();
        return *this;
    }
    DETAIL_PHI_MAKE_OP(-=)

    template <typename T, typename = detail::enable_safe_integer_conversion<T, IntegerT>>
    CPP_ALWAYS_INLINE Integer& operator*=(const Integer<T>& other)
    {
        m_Value *= other.get();
        return *this;
    }
    DETAIL_PHI_MAKE_OP(*=)

    template <typename T, typename = detail::enable_safe_integer_conversion<T, IntegerT>>
    CPP_ALWAYS_INLINE Integer& operator/=(const Integer<T>& other)
    {
        m_Value /= other.get();
        return *this;
    }
    DETAIL_PHI_MAKE_OP(/=)

    template <typename T, typename = detail::enable_safe_integer_conversion<T, IntegerT>>
    CPP_ALWAYS_INLINE Integer& operator%=(const Integer<T>& other)
    {
        m_Value %= other.get();
        return *this;
    }
    DETAIL_PHI_MAKE_OP(%=)

#undef DETAIL_PHI_MAKE_OP

private:
    IntegerT m_Value;
};

//=== operations ===//
/// \cond detail
namespace detail
{
    template <typename T>
    struct make_signed
    {
        using type = typename std::make_signed_t<T>;
    };

    template <typename T>
    struct make_signed<Integer<T>>
    {
        using type = Integer<typename std::make_signed_t<T>>;
    };

    template <typename T>
    using make_signed_t = typename make_signed<T>::type;

    template <typename T>
    struct make_unsigned
    {
        using type = typename std::make_unsigned_t<T>;
    };

    template <typename T>
    struct make_unsigned<Integer<T>>
    {
        using type = Integer<typename std::make_unsigned_t<T>>;
    };

    template <typename T>
    using make_unsigned_t = typename make_unsigned<T>::type;
} // namespace detail
/// \endcond

template <typename IntegerT>
using make_signed_t = typename detail::make_signed_t<IntegerT>;

template <typename IntegerT, typename = typename std::enable_if_t<detail::is_integer_v<IntegerT>>>
CPP_ALWAYS_INLINE constexpr make_signed_t<IntegerT> make_signed(const IntegerT& val)
{
    using result_type = make_signed_t<IntegerT>;
    return static_cast<result_type>(val);
}

template <typename IntegerT>
CPP_ALWAYS_INLINE constexpr make_signed_t<Integer<IntegerT>> make_signed(
        const Integer<IntegerT>& val)
{
    return make_signed(static_cast<IntegerT>(val));
}

template <typename IntegerT>
using make_unsigned_t = typename detail::make_unsigned_t<IntegerT>;

template <typename IntegerT, typename = typename std::enable_if_t<detail::is_integer_v<IntegerT>>>
CPP_ALWAYS_INLINE constexpr make_unsigned_t<IntegerT> make_unsigned(const IntegerT& val)
{
    using result_type = make_unsigned_t<IntegerT>;
    return static_cast<result_type>(val);
}

template <typename IntegerT>
CPP_ALWAYS_INLINE constexpr make_unsigned_t<Integer<IntegerT>> make_unsigned(
        const Integer<IntegerT>& val)
{
    return make_unsigned(static_cast<IntegerT>(val));
}

template <typename SignedIntegerT,
          typename = typename std::enable_if_t<std::is_signed_v<SignedIntegerT>>>
CPP_ALWAYS_INLINE constexpr make_unsigned_t<SignedIntegerT> abs(const SignedIntegerT& val)
{
    return make_unsigned(val > 0 ? val : -val);
}

template <typename SignedIntegerT,
          typename = typename std::enable_if_t<std::is_signed_v<SignedIntegerT>>>
CPP_ALWAYS_INLINE constexpr make_unsigned_t<Integer<SignedIntegerT>> abs(
        const Integer<SignedIntegerT>& val)
{
    return make_unsigned(val > 0 ? val : -val);
}

template <typename UnsignedInteger,
          typename = typename std::enable_if_t<std::is_unsigned_v<UnsignedInteger>>>
CPP_ALWAYS_INLINE constexpr UnsignedInteger abs(const UnsignedInteger& val)
{
    return val;
}

template <typename UnsignedInteger,
          typename = typename std::enable_if_t<std::is_unsigned_v<UnsignedInteger>>>
CPP_ALWAYS_INLINE constexpr Integer<UnsignedInteger> abs(const Integer<UnsignedInteger>& val)
{
    return val;
}

//=== comparison ===//
#define DETAIL_PHI_MAKE_OP(Op)                                                                     \
    template <typename LhsT, typename RhsT,                                                        \
              typename = detail::enable_safe_integer_comparison<LhsT, RhsT>>                       \
    CPP_ALWAYS_INLINE constexpr bool operator Op(const LhsT& lhs, const Integer<RhsT>& rhs)        \
    {                                                                                              \
        return Integer<LhsT>(lhs) Op rhs;                                                          \
    }                                                                                              \
                                                                                                   \
    template <typename LhsT, typename RhsT,                                                        \
              typename = detail::enable_safe_integer_comparison<LhsT, RhsT>>                       \
    CPP_ALWAYS_INLINE constexpr bool operator Op(const Integer<LhsT>& lhs, const RhsT& rhs)        \
    {                                                                                              \
        return lhs Op Integer<RhsT>(rhs);                                                          \
    }                                                                                              \
                                                                                                   \
    template <typename LhsT, typename RhsT,                                                        \
              typename = detail::fallback_safe_integer_comparison<LhsT, RhsT>>                     \
    constexpr bool operator Op(Integer<LhsT>, Integer<RhsT>) = delete;                             \
                                                                                                   \
    template <typename LhsT, typename RhsT,                                                        \
              typename = detail::fallback_safe_integer_comparison<LhsT, RhsT>>                     \
    constexpr bool operator Op(LhsT, Integer<RhsT>) = delete;                                      \
                                                                                                   \
    template <typename LhsT, typename RhsT,                                                        \
              typename = detail::fallback_safe_integer_comparison<LhsT, RhsT>>                     \
    constexpr bool operator Op(Integer<LhsT>, RhsT) = delete;

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_integer_comparison<LhsT, RhsT>>
CPP_ALWAYS_INLINE constexpr bool operator==(const Integer<LhsT>& lhs, const Integer<RhsT>& rhs)
{
    return static_cast<LhsT>(lhs) == static_cast<RhsT>(rhs);
}
DETAIL_PHI_MAKE_OP(==)

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_integer_comparison<LhsT, RhsT>>
CPP_ALWAYS_INLINE constexpr bool operator!=(const Integer<LhsT>& lhs, const Integer<RhsT>& rhs)
{
    return static_cast<LhsT>(lhs) != static_cast<RhsT>(rhs);
}
DETAIL_PHI_MAKE_OP(!=)

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_integer_comparison<LhsT, RhsT>>
CPP_ALWAYS_INLINE constexpr bool operator<(const Integer<LhsT>& lhs, const Integer<RhsT>& rhs)
{
    return static_cast<LhsT>(lhs) < static_cast<RhsT>(rhs);
}
DETAIL_PHI_MAKE_OP(<)

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_integer_comparison<LhsT, RhsT>>
CPP_ALWAYS_INLINE constexpr bool operator<=(const Integer<LhsT>& lhs, const Integer<RhsT>& rhs)
{
    return static_cast<LhsT>(lhs) <= static_cast<RhsT>(rhs);
}
DETAIL_PHI_MAKE_OP(<=)

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_integer_comparison<LhsT, RhsT>>
CPP_ALWAYS_INLINE constexpr bool operator>(const Integer<LhsT>& lhs, const Integer<RhsT>& rhs)
{
    return static_cast<LhsT>(lhs) > static_cast<RhsT>(rhs);
}
DETAIL_PHI_MAKE_OP(>)

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_integer_comparison<LhsT, RhsT>>
CPP_ALWAYS_INLINE constexpr bool operator>=(const Integer<LhsT>& lhs, const Integer<RhsT>& rhs)
{
    return static_cast<LhsT>(lhs) >= static_cast<RhsT>(rhs);
}
DETAIL_PHI_MAKE_OP(>=)

#undef DETAIL_PHI_MAKE_OP

//=== binary operations ===//
#define DETAIL_PHI_MAKE_OP(Op)                                                                     \
    template <typename LhsT, typename RhsT>                                                        \
    CPP_ALWAYS_INLINE constexpr auto operator Op(const LhsT& lhs, const Integer<RhsT>& rhs)        \
            ->Integer<detail::integer_result_t<LhsT, RhsT>>                                        \
    {                                                                                              \
        return Integer<LhsT>(lhs) Op rhs;                                                          \
    }                                                                                              \
                                                                                                   \
    template <typename LhsT, typename RhsT>                                                        \
    CPP_ALWAYS_INLINE constexpr auto operator Op(const Integer<LhsT>& lhs, const RhsT& rhs)        \
            ->Integer<detail::integer_result_t<LhsT, RhsT>>                                        \
    {                                                                                              \
        return lhs Op Integer<RhsT>(rhs);                                                          \
    }                                                                                              \
                                                                                                   \
    template <typename LhsT, typename RhsT,                                                        \
              typename = detail::fallback_integer_result<LhsT, RhsT>>                              \
    constexpr int operator Op(Integer<LhsT>, Integer<RhsT>) = delete;                              \
                                                                                                   \
    template <typename LhsT, typename RhsT,                                                        \
              typename = detail::fallback_integer_result<LhsT, RhsT>>                              \
    constexpr int operator Op(LhsT, Integer<RhsT>) = delete;                                       \
                                                                                                   \
    template <typename LhsT, typename RhsT,                                                        \
              typename = detail::fallback_integer_result<LhsT, RhsT>>                              \
    constexpr int operator Op(Integer<LhsT>, RhsT) = delete;

template <typename LhsT, typename RhsT>
CPP_ALWAYS_INLINE constexpr auto operator+(const Integer<LhsT>& lhs, const Integer<RhsT>& rhs)
        -> Integer<detail::integer_result_t<LhsT, RhsT>>
{
    using type = detail::integer_result_t<LhsT, RhsT>;
    return Integer<type>(static_cast<LhsT>(lhs) + static_cast<RhsT>(rhs));
}
DETAIL_PHI_MAKE_OP(+)

template <typename LhsT, typename RhsT>
CPP_ALWAYS_INLINE constexpr auto operator-(const Integer<LhsT>& lhs, const Integer<RhsT>& rhs)
        -> Integer<detail::integer_result_t<LhsT, RhsT>>
{
    using type = detail::integer_result_t<LhsT, RhsT>;
    return Integer<type>(static_cast<LhsT>(lhs) - static_cast<RhsT>(rhs));
}
DETAIL_PHI_MAKE_OP(-)

template <typename LhsT, typename RhsT>
CPP_ALWAYS_INLINE constexpr auto operator*(const Integer<LhsT>& lhs, const Integer<RhsT>& rhs)
        -> Integer<detail::integer_result_t<LhsT, RhsT>>
{
    using type = detail::integer_result_t<LhsT, RhsT>;
    return Integer<type>(static_cast<LhsT>(lhs) * static_cast<RhsT>(rhs));
}
DETAIL_PHI_MAKE_OP(*)

template <typename LhsT, typename RhsT>
CPP_ALWAYS_INLINE constexpr auto operator/(const Integer<LhsT>& lhs, const Integer<RhsT>& rhs)
        -> Integer<detail::integer_result_t<LhsT, RhsT>>
{
    using type = detail::integer_result_t<LhsT, RhsT>;
    return Integer<type>(static_cast<LhsT>(lhs) / static_cast<RhsT>(rhs));
}
DETAIL_PHI_MAKE_OP(/)

template <typename LhsT, typename RhsT>
CPP_ALWAYS_INLINE constexpr auto operator%(const Integer<LhsT>& lhs, const Integer<RhsT>& rhs)
        -> Integer<detail::integer_result_t<LhsT, RhsT>>
{
    using type = detail::integer_result_t<LhsT, RhsT>;
    return Integer<type>(static_cast<LhsT>(lhs) % static_cast<RhsT>(rhs));
}
DETAIL_PHI_MAKE_OP(%)

#undef DETAIL_PHI_MAKE_OP

//=== input/output ===/
template <typename CharT, typename CharTraitsT, typename IntegerT>
std::basic_istream<CharT, CharTraitsT>& operator>>(std::basic_istream<CharT, CharTraitsT>& stream,
                                                   Integer<IntegerT>&                      i)
{
    IntegerT val;
    stream >> val;
    i = val;
    return stream;
}

template <typename CharT, typename CharTraitsT, typename IntegerT>
std::basic_ostream<CharT, CharTraitsT>& operator<<(std::basic_ostream<CharT, CharTraitsT>& stream,
                                                   const Integer<IntegerT>&                val)
{
    return stream << static_cast<IntegerT>(val);
}

DETAIL_PHI_END_NAMESPACE()

namespace std
{
    /// Hash specialization for [phi::Integer].
    template <typename IntegerT>
    struct hash<phi::Integer<IntegerT>>
    {
        std::size_t operator()(const phi::Integer<IntegerT>& val) const noexcept
        {
            return std::hash<IntegerT>()(static_cast<IntegerT>(val));
        }
    };
} // namespace std

#endif // INCG_PHI_UTILITY_INTEGER_HPP
