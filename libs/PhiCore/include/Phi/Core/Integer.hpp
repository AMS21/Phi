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

#include "Phi/Config/Inline.hpp"
#include "Phi/Config/Warning.hpp"
#include "Phi/Core/Assert.hpp"
#include "Phi/Core/Boolean.hpp"
#include "Phi/PhiConfig.hpp"
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
    template <typename TypeT>
    struct is_integer
        : std::bool_constant<std::is_integral_v<TypeT> && !std::is_same_v<TypeT, bool> &&
                             !std::is_same_v<TypeT, char> && !std::is_same_v<TypeT, wchar_t> &&
                             !std::is_same_v<TypeT, char16_t> && !std::is_same_v<TypeT, char32_t>>
    {};

    // Integer conversion
    template <typename FromT, typename ToT>
    struct is_safe_integer_conversion
        : std::bool_constant<detail::is_integer<FromT>::value && detail::is_integer<ToT>::value &&
                             ((sizeof(FromT) <= sizeof(ToT) &&
                               std::is_signed_v<FromT> == std::is_signed_v<ToT>) ||
                              (sizeof(FromT) < sizeof(ToT) && std::is_unsigned_v<FromT> &&
                               std::is_signed_v<ToT>))>
    {};

    template <typename FromT, typename ToT>
    using enable_safe_integer_conversion =
            typename std::enable_if_t<is_safe_integer_conversion<FromT, ToT>::value>;

    template <typename FromT, typename ToT>
    using fallback_safe_integer_conversion =
            typename std::enable_if_t<!is_safe_integer_conversion<FromT, ToT>::value>;

    // Integer comparison
    template <typename LhsT, typename RhsT>
    struct is_safe_integer_comparison
        : std::bool_constant<is_safe_integer_conversion<LhsT, RhsT>::value ||
                             is_safe_integer_conversion<RhsT, LhsT>::value>
    {};

    template <typename LhsT, typename RhsT>
    using enable_safe_integer_comparison =
            typename std::enable_if_t<is_safe_integer_comparison<LhsT, RhsT>::value>;

    template <typename LhsT, typename RhsT>
    using fallback_safe_integer_comparison =
            typename std::enable_if_t<!is_safe_integer_comparison<LhsT, RhsT>::value>;

    // Integer operation
    template <typename LhsT, typename RhsT>
    struct is_safe_integer_operation
        : std::bool_constant<is_integer<LhsT>::value && is_integer<RhsT>::value &&
                             std::is_signed_v<LhsT> == std::is_signed_v<RhsT>>
    {};

    template <typename LhsT, typename RhsT>
    struct integer_result_type
        : std::enable_if<is_safe_integer_operation<LhsT, RhsT>::value,
                         typename std::conditional_t<sizeof(LhsT) < sizeof(RhsT), RhsT, LhsT>>
    {};

    template <typename LhsT, typename RhsT>
    using integer_result_t = typename integer_result_type<LhsT, RhsT>::type;

    template <typename LhsT, typename RhsT>
    using fallback_integer_result =
            typename std::enable_if_t<is_integer<LhsT>::value && is_integer<RhsT>::value &&
                                      std::is_signed_v<LhsT> != std::is_signed_v<RhsT>>;

    // Error detection
    struct signed_integer_tag
    {};

    struct unsigned_integer_tag
    {};

    template <typename TypeT>
    using arithmetic_tag_for =
            typename std::conditional_t<std::is_signed<TypeT>::value, signed_integer_tag,
                                        unsigned_integer_tag>;

    template <typename TypeT>
    PHI_ALWAYS_INLINE constexpr bool will_addition_error(signed_integer_tag tag, TypeT lhs,
                                                         TypeT rhs) noexcept
    {
        PHI_UNUSED_PARAMETER(tag);

        return rhs > TypeT(0) ? lhs > std::numeric_limits<TypeT>::max() - rhs :
                                lhs < std::numeric_limits<TypeT>::min() - rhs;
    }

    template <typename TypeT>
    PHI_ALWAYS_INLINE constexpr bool will_addition_error(unsigned_integer_tag tag, TypeT lhs,
                                                         TypeT rhs) noexcept
    {
        PHI_UNUSED_PARAMETER(tag);

        return std::numeric_limits<TypeT>::max() - rhs < lhs;
    }

    template <typename TypeT>
    PHI_ALWAYS_INLINE constexpr bool will_subtraction_error(signed_integer_tag tag, TypeT lhs,
                                                            TypeT rhs) noexcept
    {
        PHI_UNUSED_PARAMETER(tag);

        return rhs > TypeT(0) ? lhs < std::numeric_limits<TypeT>::min() + rhs :
                                lhs > std::numeric_limits<TypeT>::max() + rhs;
    }

    template <typename TypeT>
    PHI_ALWAYS_INLINE constexpr bool will_subtraction_error(unsigned_integer_tag tag, TypeT lhs,
                                                            TypeT rhs) noexcept
    {
        PHI_UNUSED_PARAMETER(tag);

        return lhs < rhs;
    }

    template <typename TypeT>
    PHI_ALWAYS_INLINE constexpr bool will_multiplication_error(signed_integer_tag tag, TypeT lhs,
                                                               TypeT rhs) noexcept
    {
        PHI_UNUSED_PARAMETER(tag);

        return lhs > TypeT(0) ?
                       (rhs > TypeT(0) ?
                                lhs > std::numeric_limits<TypeT>::max() / rhs : // lhs, rhs > 0
                                rhs < std::numeric_limits<TypeT>::min() /
                                                lhs) : // lhs > 0, rhs <= 0
                       (rhs > TypeT(0) ?
                                lhs < std::numeric_limits<TypeT>::min() / rhs : // lhs <= 0, rhs > 0
                                lhs != TypeT(0) && rhs < std::numeric_limits<TypeT>::max() /
                                                                   lhs); // lhs, rhs <= 0
    }

    template <typename TypeT>
    PHI_ALWAYS_INLINE constexpr bool will_multiplication_error(unsigned_integer_tag tag, TypeT lhs,
                                                               TypeT rhs) noexcept
    {
        PHI_UNUSED_PARAMETER(tag);

        return rhs != TypeT(0) && lhs > std::numeric_limits<TypeT>::max() / rhs;
    }

    template <typename TypeT>
    PHI_ALWAYS_INLINE constexpr bool will_division_error(signed_integer_tag tag, TypeT lhs,
                                                         TypeT rhs) noexcept
    {
        PHI_UNUSED_PARAMETER(tag);

        return rhs == TypeT(0) || (rhs == TypeT(-1) && lhs == std::numeric_limits<TypeT>::min());
    }

    template <typename TypeT>
    PHI_ALWAYS_INLINE constexpr bool will_division_error(unsigned_integer_tag tag, TypeT lhs,
                                                         TypeT rhs) noexcept
    {
        PHI_UNUSED_PARAMETER(tag);
        PHI_UNUSED_PARAMETER(lhs);

        return rhs == TypeT(0);
    }

    template <typename TypeT>
    PHI_ALWAYS_INLINE constexpr bool will_modulo_error(signed_integer_tag tag, TypeT lhs,
                                                       TypeT rhs) noexcept
    {
        PHI_UNUSED_PARAMETER(tag);
        PHI_UNUSED_PARAMETER(lhs);

        return rhs == TypeT(0);
    }

    template <typename TypeT>
    PHI_ALWAYS_INLINE constexpr bool will_modulo_error(unsigned_integer_tag tag, TypeT lhs,
                                                       TypeT rhs) noexcept
    {
        PHI_UNUSED_PARAMETER(tag);
        PHI_UNUSED_PARAMETER(lhs);

        return rhs == TypeT(0);
    }
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
    static_assert(detail::is_integer<IntegerT>::value,
                  "[phi::Integer] Must be a real integer type");

public:
    using this_type   = Integer<IntegerT>;
    using value_type  = IntegerT;
    using limits_type = std::numeric_limits<IntegerT>;

    //=== constructors ===//

    Integer() = delete;

    template <typename TypeT, typename = detail::enable_safe_integer_conversion<TypeT, IntegerT>>
    // cppcheck-suppress noExplicitConstructor; NOLINTNEXTLINE(hicpp-explicit-conversions)
    PHI_ALWAYS_INLINE constexpr Integer(const TypeT& val) noexcept
        : m_Value(val)
    {}

    template <typename TypeT, typename = detail::enable_safe_integer_conversion<TypeT, IntegerT>>
    // cppcheck-suppress noExplicitConstructor; NOLINTNEXTLINE(hicpp-explicit-conversions)
    PHI_ALWAYS_INLINE constexpr Integer(const Integer<TypeT>& val) noexcept
        : m_Value(static_cast<TypeT>(val))
    {}

    template <typename TypeT, typename = detail::fallback_safe_integer_conversion<TypeT, IntegerT>>
    constexpr Integer(TypeT) = delete;

    //=== assignment ===//

    template <typename TypeT, typename = detail::enable_safe_integer_conversion<TypeT, IntegerT>>
    PHI_ALWAYS_INLINE Integer& operator=(const TypeT& val) noexcept
    {
        m_Value = val;
        return *this;
    }

    template <typename TypeT, typename = detail::enable_safe_integer_conversion<TypeT, IntegerT>>
    PHI_ALWAYS_INLINE Integer& operator=(const Integer<TypeT>& val) noexcept
    {
        m_Value = static_cast<TypeT>(val);
        return *this;
    }

    //=== conversion back ===//

    [[nodiscard]] PHI_ALWAYS_INLINE explicit constexpr operator IntegerT() const noexcept
    {
        return m_Value;
    }

    [[nodiscard]] PHI_ALWAYS_INLINE constexpr IntegerT get() const noexcept
    {
        return m_Value;
    }

    [[nodiscard]] PHI_ALWAYS_INLINE constexpr static Integer<IntegerT> min() noexcept
    {
        return limits_type::min();
    }

    [[nodiscard]] PHI_ALWAYS_INLINE constexpr static Integer<IntegerT> max() noexcept
    {
        return limits_type::max();
    }

    //=== unary operators ===//
    PHI_ALWAYS_INLINE constexpr Integer operator+() const noexcept
    {
        return *this;
    }

    PHI_ALWAYS_INLINE constexpr Integer operator-() const noexcept
    {
        static_assert(std::is_signed_v<IntegerT>, "Cannot call unary minus on unsigned integer");

        PHI_DBG_ASSERT(m_Value != limits_type::min(), "Unary minus will overflow. Args {}",
                       m_Value);

        return Integer(-m_Value);
    }

    PHI_ALWAYS_INLINE constexpr Integer& operator++() noexcept
    {
        PHI_DBG_ASSERT(!detail::will_addition_error(detail::arithmetic_tag_for<IntegerT>{}, m_Value,
                                                    IntegerT(1)),
                       "Operator++ will result in overflow. Args {}", m_Value);

        m_Value += 1;
        return *this;
    }

    // cppcheck-suppress functionConst; NOLINTNEXTLINE(readability-const-return-type)
    PHI_ALWAYS_INLINE constexpr const Integer operator++(int) noexcept
    {
        auto res = *this;
        ++*this;
        return res;
    }

    PHI_ALWAYS_INLINE constexpr Integer& operator--() noexcept
    {
        PHI_DBG_ASSERT(!detail::will_subtraction_error(detail::arithmetic_tag_for<IntegerT>{},
                                                       m_Value, IntegerT(1)),
                       "Operator-- will result in underflow. Args {}", m_Value);

        m_Value -= 1;
        return *this;
    }

    // cppcheck-suppress functionConst; NOLINTNEXTLINE(readability-const-return-type)
    PHI_ALWAYS_INLINE constexpr const Integer operator--(int) noexcept
    {
        auto res = *this;
        --*this;
        return res;
    }

    //=== compound assignment ====//

    template <typename TypeT, typename = detail::enable_safe_integer_conversion<TypeT, IntegerT>>
    PHI_ALWAYS_INLINE constexpr Integer& operator+=(const Integer<TypeT>& other) noexcept
    {
        PHI_DBG_ASSERT(!detail::will_addition_error<IntegerT>(
                               detail::arithmetic_tag_for<IntegerT>{}, m_Value, other.get()),
                       "Addition will result in overflow. Args {} + {}", m_Value, other.get());

        m_Value += other.get();
        return *this;
    }

    template <typename TypeT, typename = detail::enable_safe_integer_conversion<TypeT, IntegerT>>
    PHI_ALWAYS_INLINE constexpr Integer& operator+=(const TypeT& other) noexcept
    {
        return *this += Integer<TypeT>(other);
    }

    template <typename TypeT, typename = detail::fallback_safe_integer_conversion<TypeT, IntegerT>>
    Integer& operator+=(Integer<TypeT>) = delete;

    template <typename TypeT, typename = detail::fallback_safe_integer_conversion<TypeT, IntegerT>>
    Integer& operator+=(TypeT) = delete;

    template <typename TypeT, typename = detail::enable_safe_integer_conversion<TypeT, IntegerT>>
    PHI_ALWAYS_INLINE constexpr Integer& operator-=(const Integer<TypeT>& other) noexcept
    {
        PHI_DBG_ASSERT(!detail::will_subtraction_error<IntegerT>(
                               detail::arithmetic_tag_for<IntegerT>{}, m_Value, other.get()),
                       "Subtraction will result in underflow. Args {} - {}", m_Value, other.get());

        m_Value -= other.get();
        return *this;
    }

    template <typename TypeT, typename = detail::enable_safe_integer_conversion<TypeT, IntegerT>>
    PHI_ALWAYS_INLINE constexpr Integer& operator-=(const TypeT& other) noexcept
    {
        return *this -= Integer<TypeT>(other);
    }

    template <typename TypeT, typename = detail::fallback_safe_integer_conversion<TypeT, IntegerT>>
    Integer& operator-=(Integer<TypeT>) = delete;

    template <typename TypeT, typename = detail::fallback_safe_integer_conversion<TypeT, IntegerT>>
    Integer& operator-=(TypeT) = delete;

    template <typename TypeT, typename = detail::enable_safe_integer_conversion<TypeT, IntegerT>>
    PHI_ALWAYS_INLINE constexpr Integer& operator*=(const Integer<TypeT>& other) noexcept
    {
        PHI_DBG_ASSERT(!detail::will_multiplication_error<IntegerT>(
                               detail::arithmetic_tag_for<IntegerT>{}, m_Value, other.get()),
                       "Multiplication will result in overflow. Args {} * {}", m_Value,
                       other.get());

        m_Value *= other.get();
        return *this;
    }

    template <typename TypeT, typename = detail::enable_safe_integer_conversion<TypeT, IntegerT>>
    PHI_ALWAYS_INLINE constexpr Integer& operator*=(const TypeT& other) noexcept
    {
        return *this *= Integer<TypeT>(other);
    }

    template <typename TypeT, typename = detail::fallback_safe_integer_conversion<TypeT, IntegerT>>
    Integer& operator*=(Integer<TypeT>) = delete;

    template <typename TypeT, typename = detail::fallback_safe_integer_conversion<TypeT, IntegerT>>
    Integer& operator*=(TypeT) = delete;

    template <typename TypeT, typename = detail::enable_safe_integer_conversion<TypeT, IntegerT>>
    PHI_ALWAYS_INLINE constexpr Integer& operator/=(const Integer<TypeT>& other) noexcept
    {
        PHI_DBG_ASSERT(!detail::will_division_error<IntegerT>(
                               detail::arithmetic_tag_for<IntegerT>{}, m_Value, other.get()),
                       "Division error. Args {} / {}", m_Value, other.get());

        m_Value /= other.get();
        return *this;
    }

    template <typename TypeT, typename = detail::enable_safe_integer_conversion<TypeT, IntegerT>>
    PHI_ALWAYS_INLINE constexpr Integer& operator/=(const TypeT& other) noexcept
    {
        return *this /= Integer<TypeT>(other);
    }

    template <typename TypeT, typename = detail::fallback_safe_integer_conversion<TypeT, IntegerT>>
    Integer& operator/=(Integer<TypeT>) = delete;

    template <typename TypeT, typename = detail::fallback_safe_integer_conversion<TypeT, IntegerT>>
    Integer& operator/=(TypeT) = delete;

    template <typename TypeT, typename = detail::enable_safe_integer_conversion<TypeT, IntegerT>>
    PHI_ALWAYS_INLINE constexpr Integer& operator%=(const Integer<TypeT>& other) noexcept
    {
        PHI_DBG_ASSERT(!detail::will_modulo_error<IntegerT>(detail::arithmetic_tag_for<IntegerT>{},
                                                            m_Value, other.get()),
                       "Modulo error. Args {} % {}", m_Value, other.get());

        m_Value %= other.get();
        return *this;
    }

    template <typename TypeT, typename = detail::enable_safe_integer_conversion<TypeT, IntegerT>>
    PHI_ALWAYS_INLINE constexpr Integer& operator%=(const TypeT& other) noexcept
    {
        return *this %= Integer<TypeT>(other);
    }

    template <typename TypeT, typename = detail::fallback_safe_integer_conversion<TypeT, IntegerT>>
    Integer& operator%=(Integer<TypeT>) = delete;

    template <typename TypeT, typename = detail::fallback_safe_integer_conversion<TypeT, IntegerT>>
    Integer& operator%=(TypeT) = delete;

private:
    IntegerT m_Value;
};

//=== comparison ===//

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_integer_comparison<LhsT, RhsT>>
PHI_ALWAYS_INLINE constexpr Boolean operator==(const Integer<LhsT>& lhs,
                                               const Integer<RhsT>& rhs) noexcept
{
    return static_cast<LhsT>(lhs) == static_cast<RhsT>(rhs);
}

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_integer_comparison<LhsT, RhsT>>
PHI_ALWAYS_INLINE constexpr Boolean operator==(const LhsT& lhs, const Integer<RhsT>& rhs) noexcept
{
    return Integer<LhsT>(lhs) == rhs;
}

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_integer_comparison<LhsT, RhsT>>
PHI_ALWAYS_INLINE constexpr Boolean operator==(const Integer<LhsT>& lhs, const RhsT& rhs) noexcept
{
    return lhs == Integer<RhsT>(rhs);
}

template <typename LhsT, typename RhsT,
          typename = detail::fallback_safe_integer_comparison<LhsT, RhsT>>
constexpr Boolean operator==(Integer<LhsT>, Integer<RhsT>) = delete;

template <typename LhsT, typename RhsT,
          typename = detail::fallback_safe_integer_comparison<LhsT, RhsT>>
constexpr Boolean operator==(LhsT, Integer<RhsT>) = delete;

template <typename LhsT, typename RhsT,
          typename = detail::fallback_safe_integer_comparison<LhsT, RhsT>>
constexpr Boolean operator==(Integer<LhsT>, RhsT) = delete;

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_integer_comparison<LhsT, RhsT>>
PHI_ALWAYS_INLINE constexpr Boolean operator!=(const Integer<LhsT>& lhs,
                                               const Integer<RhsT>& rhs) noexcept
{
    return static_cast<LhsT>(lhs) != static_cast<RhsT>(rhs);
}

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_integer_comparison<LhsT, RhsT>>
PHI_ALWAYS_INLINE constexpr Boolean operator!=(const LhsT& lhs, const Integer<RhsT>& rhs) noexcept
{
    return Integer<LhsT>(lhs) != rhs;
}

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_integer_comparison<LhsT, RhsT>>
PHI_ALWAYS_INLINE constexpr Boolean operator!=(const Integer<LhsT>& lhs, const RhsT& rhs) noexcept
{
    return lhs != Integer<RhsT>(rhs);
}

template <typename LhsT, typename RhsT,
          typename = detail::fallback_safe_integer_comparison<LhsT, RhsT>>
constexpr Boolean operator!=(Integer<LhsT>, Integer<RhsT>) = delete;

template <typename LhsT, typename RhsT,
          typename = detail::fallback_safe_integer_comparison<LhsT, RhsT>>
constexpr Boolean operator!=(LhsT, Integer<RhsT>) = delete;

template <typename LhsT, typename RhsT,
          typename = detail::fallback_safe_integer_comparison<LhsT, RhsT>>
constexpr Boolean operator!=(Integer<LhsT>, RhsT) = delete;

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_integer_comparison<LhsT, RhsT>>
PHI_ALWAYS_INLINE constexpr Boolean operator<(const Integer<LhsT>& lhs,
                                              const Integer<RhsT>& rhs) noexcept
{
    return static_cast<LhsT>(lhs) < static_cast<RhsT>(rhs);
}

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_integer_comparison<LhsT, RhsT>>
PHI_ALWAYS_INLINE constexpr Boolean operator<(const LhsT& lhs, const Integer<RhsT>& rhs) noexcept
{
    return Integer<LhsT>(lhs) < rhs;
}

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_integer_comparison<LhsT, RhsT>>
PHI_ALWAYS_INLINE constexpr Boolean operator<(const Integer<LhsT>& lhs, const RhsT& rhs) noexcept
{
    return lhs < Integer<RhsT>(rhs);
}

template <typename LhsT, typename RhsT,
          typename = detail::fallback_safe_integer_comparison<LhsT, RhsT>>
constexpr Boolean operator<(Integer<LhsT>, Integer<RhsT>) = delete;

template <typename LhsT, typename RhsT,
          typename = detail::fallback_safe_integer_comparison<LhsT, RhsT>>
constexpr Boolean operator<(LhsT, Integer<RhsT>) = delete;

template <typename LhsT, typename RhsT,
          typename = detail::fallback_safe_integer_comparison<LhsT, RhsT>>
constexpr Boolean operator<(Integer<LhsT>, RhsT) = delete;

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_integer_comparison<LhsT, RhsT>>
PHI_ALWAYS_INLINE constexpr Boolean operator<=(const Integer<LhsT>& lhs,
                                               const Integer<RhsT>& rhs) noexcept
{
    return static_cast<LhsT>(lhs) <= static_cast<RhsT>(rhs);
}

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_integer_comparison<LhsT, RhsT>>
PHI_ALWAYS_INLINE constexpr Boolean operator<=(const LhsT& lhs, const Integer<RhsT>& rhs) noexcept
{
    return Integer<LhsT>(lhs) <= rhs;
}

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_integer_comparison<LhsT, RhsT>>
PHI_ALWAYS_INLINE constexpr Boolean operator<=(const Integer<LhsT>& lhs, const RhsT& rhs) noexcept
{
    return lhs <= Integer<RhsT>(rhs);
}

template <typename LhsT, typename RhsT,
          typename = detail::fallback_safe_integer_comparison<LhsT, RhsT>>
constexpr Boolean operator<=(Integer<LhsT>, Integer<RhsT>) = delete;

template <typename LhsT, typename RhsT,
          typename = detail::fallback_safe_integer_comparison<LhsT, RhsT>>
constexpr Boolean operator<=(LhsT, Integer<RhsT>) = delete;

template <typename LhsT, typename RhsT,
          typename = detail::fallback_safe_integer_comparison<LhsT, RhsT>>
constexpr Boolean operator<=(Integer<LhsT>, RhsT) = delete;

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_integer_comparison<LhsT, RhsT>>
PHI_ALWAYS_INLINE constexpr Boolean operator>(const Integer<LhsT>& lhs,
                                              const Integer<RhsT>& rhs) noexcept
{
    return static_cast<LhsT>(lhs) > static_cast<RhsT>(rhs);
}

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_integer_comparison<LhsT, RhsT>>
PHI_ALWAYS_INLINE constexpr Boolean operator>(const LhsT& lhs, const Integer<RhsT>& rhs) noexcept
{
    return Integer<LhsT>(lhs) > rhs;
}

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_integer_comparison<LhsT, RhsT>>
PHI_ALWAYS_INLINE constexpr Boolean operator>(const Integer<LhsT>& lhs, const RhsT& rhs) noexcept
{
    return lhs > Integer<RhsT>(rhs);
}

template <typename LhsT, typename RhsT,
          typename = detail::fallback_safe_integer_comparison<LhsT, RhsT>>
constexpr Boolean operator>(Integer<LhsT>, Integer<RhsT>) = delete;

template <typename LhsT, typename RhsT,
          typename = detail::fallback_safe_integer_comparison<LhsT, RhsT>>
constexpr Boolean operator>(LhsT, Integer<RhsT>) = delete;

template <typename LhsT, typename RhsT,
          typename = detail::fallback_safe_integer_comparison<LhsT, RhsT>>
constexpr Boolean operator>(Integer<LhsT>, RhsT) = delete;

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_integer_comparison<LhsT, RhsT>>
PHI_ALWAYS_INLINE constexpr Boolean operator>=(const Integer<LhsT>& lhs,
                                               const Integer<RhsT>& rhs) noexcept
{
    return static_cast<LhsT>(lhs) >= static_cast<RhsT>(rhs);
}

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_integer_comparison<LhsT, RhsT>>
PHI_ALWAYS_INLINE constexpr Boolean operator>=(const LhsT& lhs, const Integer<RhsT>& rhs) noexcept
{
    return Integer<LhsT>(lhs) >= rhs;
}

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_integer_comparison<LhsT, RhsT>>
PHI_ALWAYS_INLINE constexpr Boolean operator>=(const Integer<LhsT>& lhs, const RhsT& rhs) noexcept
{
    return lhs >= Integer<RhsT>(rhs);
}

template <typename LhsT, typename RhsT,
          typename = detail::fallback_safe_integer_comparison<LhsT, RhsT>>
constexpr Boolean operator>=(Integer<LhsT>, Integer<RhsT>) = delete;

template <typename LhsT, typename RhsT,
          typename = detail::fallback_safe_integer_comparison<LhsT, RhsT>>
constexpr Boolean operator>=(LhsT, Integer<RhsT>) = delete;

template <typename LhsT, typename RhsT,
          typename = detail::fallback_safe_integer_comparison<LhsT, RhsT>>
constexpr Boolean operator>=(Integer<LhsT>, RhsT) = delete;

//=== binary operations ===//

template <typename LhsT, typename RhsT>
PHI_ALWAYS_INLINE constexpr auto operator+(const Integer<LhsT>& lhs,
                                           const Integer<RhsT>& rhs) noexcept
        -> Integer<detail::integer_result_t<LhsT, RhsT>>
{
    using type = detail::integer_result_t<LhsT, RhsT>;
    PHI_DBG_ASSERT(!detail::will_addition_error(detail::arithmetic_tag_for<type>{},
                                                static_cast<type>(lhs.get()),
                                                static_cast<type>(rhs.get())),
                   "Addition will result in overflow. Args {} + {}", lhs.get(), rhs.get());

    return Integer<type>(static_cast<type>(static_cast<LhsT>(lhs) + static_cast<RhsT>(rhs)));
}

template <typename LhsT, typename RhsT>
PHI_ALWAYS_INLINE constexpr auto operator+(const LhsT& lhs, const Integer<RhsT>& rhs) noexcept
        -> Integer<detail::integer_result_t<LhsT, RhsT>>
{
    return Integer<LhsT>(lhs) + rhs;
}

template <typename LhsT, typename RhsT>
PHI_ALWAYS_INLINE constexpr auto operator+(const Integer<LhsT>& lhs, const RhsT& rhs) noexcept
        -> Integer<detail::integer_result_t<LhsT, RhsT>>
{
    return lhs + Integer<RhsT>(rhs);
}

template <typename LhsT, typename RhsT, typename = detail::fallback_integer_result<LhsT, RhsT>>
constexpr int operator+(Integer<LhsT>, Integer<RhsT>) = delete;

template <typename LhsT, typename RhsT, typename = detail::fallback_integer_result<LhsT, RhsT>>
constexpr int operator+(LhsT, Integer<RhsT>) = delete;

template <typename LhsT, typename RhsT, typename = detail::fallback_integer_result<LhsT, RhsT>>
constexpr int operator+(Integer<LhsT>, RhsT) = delete;

template <typename LhsT, typename RhsT>
PHI_ALWAYS_INLINE constexpr auto operator-(const Integer<LhsT>& lhs,
                                           const Integer<RhsT>& rhs) noexcept
        -> Integer<detail::integer_result_t<LhsT, RhsT>>
{
    using type = detail::integer_result_t<LhsT, RhsT>;
    PHI_DBG_ASSERT(!detail::will_subtraction_error(detail::arithmetic_tag_for<type>{},
                                                   static_cast<type>(lhs.get()),
                                                   static_cast<type>(rhs.get())),
                   "Subtraction will result in underflow. Args {} - {}", lhs.get(), rhs.get());

    return Integer<type>(static_cast<type>(static_cast<LhsT>(lhs) - static_cast<RhsT>(rhs)));
}

template <typename LhsT, typename RhsT>
PHI_ALWAYS_INLINE constexpr auto operator-(const LhsT& lhs, const Integer<RhsT>& rhs) noexcept
        -> Integer<detail::integer_result_t<LhsT, RhsT>>
{
    return Integer<LhsT>(lhs) - rhs;
}

template <typename LhsT, typename RhsT>
PHI_ALWAYS_INLINE constexpr auto operator-(const Integer<LhsT>& lhs, const RhsT& rhs) noexcept
        -> Integer<detail::integer_result_t<LhsT, RhsT>>
{
    return lhs - Integer<RhsT>(rhs);
}

template <typename LhsT, typename RhsT, typename = detail::fallback_integer_result<LhsT, RhsT>>
constexpr int operator-(Integer<LhsT>, Integer<RhsT>) = delete;

template <typename LhsT, typename RhsT, typename = detail::fallback_integer_result<LhsT, RhsT>>
constexpr int operator-(LhsT, Integer<RhsT>) = delete;

template <typename LhsT, typename RhsT, typename = detail::fallback_integer_result<LhsT, RhsT>>
constexpr int operator-(Integer<LhsT>, RhsT) = delete;

template <typename LhsT, typename RhsT>
PHI_ALWAYS_INLINE constexpr auto operator*(const Integer<LhsT>& lhs,
                                           const Integer<RhsT>& rhs) noexcept
        -> Integer<detail::integer_result_t<LhsT, RhsT>>
{
    using type = detail::integer_result_t<LhsT, RhsT>;
    PHI_DBG_ASSERT(!detail::will_multiplication_error(detail::arithmetic_tag_for<type>{},
                                                      static_cast<type>(lhs.get()),
                                                      static_cast<type>(rhs.get())),
                   "Multiplication will result in overflow. Args {} * {}", lhs.get(), rhs.get());

    return Integer<type>(static_cast<type>(static_cast<LhsT>(lhs) * static_cast<RhsT>(rhs)));
}

template <typename LhsT, typename RhsT>
PHI_ALWAYS_INLINE constexpr auto operator*(const LhsT& lhs, const Integer<RhsT>& rhs) noexcept
        -> Integer<detail::integer_result_t<LhsT, RhsT>>
{
    return Integer<LhsT>(lhs) * rhs;
}

template <typename LhsT, typename RhsT>
PHI_ALWAYS_INLINE constexpr auto operator*(const Integer<LhsT>& lhs, const RhsT& rhs) noexcept
        -> Integer<detail::integer_result_t<LhsT, RhsT>>
{
    return lhs * Integer<RhsT>(rhs);
}

template <typename LhsT, typename RhsT, typename = detail::fallback_integer_result<LhsT, RhsT>>
constexpr int operator*(Integer<LhsT>, Integer<RhsT>) = delete;

template <typename LhsT, typename RhsT, typename = detail::fallback_integer_result<LhsT, RhsT>>
constexpr int operator*(LhsT, Integer<RhsT>) = delete;

template <typename LhsT, typename RhsT, typename = detail::fallback_integer_result<LhsT, RhsT>>
constexpr int operator*(Integer<LhsT>, RhsT) = delete;

template <typename LhsT, typename RhsT>
PHI_ALWAYS_INLINE constexpr auto operator/(const Integer<LhsT>& lhs,
                                           const Integer<RhsT>& rhs) noexcept
        -> Integer<detail::integer_result_t<LhsT, RhsT>>
{
    using type = detail::integer_result_t<LhsT, RhsT>;
    PHI_DBG_ASSERT(!detail::will_division_error(detail::arithmetic_tag_for<type>{},
                                                static_cast<type>(lhs.get()),
                                                static_cast<type>(rhs.get())),
                   "Division by zero/overflow. Args {} / {}", lhs.get(), rhs.get());

    return Integer<type>(static_cast<type>(static_cast<LhsT>(lhs) / static_cast<RhsT>(rhs)));
}

template <typename LhsT, typename RhsT>
PHI_ALWAYS_INLINE constexpr auto operator/(const LhsT& lhs, const Integer<RhsT>& rhs) noexcept
        -> Integer<detail::integer_result_t<LhsT, RhsT>>
{
    return Integer<LhsT>(lhs) / rhs;
}

template <typename LhsT, typename RhsT>
PHI_ALWAYS_INLINE constexpr auto operator/(const Integer<LhsT>& lhs, const RhsT& rhs) noexcept
        -> Integer<detail::integer_result_t<LhsT, RhsT>>
{
    return lhs / Integer<RhsT>(rhs);
}

template <typename LhsT, typename RhsT, typename = detail::fallback_integer_result<LhsT, RhsT>>
constexpr int operator/(Integer<LhsT>, Integer<RhsT>) = delete;

template <typename LhsT, typename RhsT, typename = detail::fallback_integer_result<LhsT, RhsT>>
constexpr int operator/(LhsT, Integer<RhsT>) = delete;

template <typename LhsT, typename RhsT, typename = detail::fallback_integer_result<LhsT, RhsT>>
constexpr int operator/(Integer<LhsT>, RhsT) = delete;

template <typename LhsT, typename RhsT>
PHI_ALWAYS_INLINE constexpr auto operator%(const Integer<LhsT>& lhs,
                                           const Integer<RhsT>& rhs) noexcept
        -> Integer<detail::integer_result_t<LhsT, RhsT>>
{
    using type = detail::integer_result_t<LhsT, RhsT>;
    PHI_DBG_ASSERT(!detail::will_modulo_error(detail::arithmetic_tag_for<type>{},
                                              static_cast<type>(lhs.get()),
                                              static_cast<type>(rhs.get())),
                   "Modulo by zero. Args {} % {}", lhs.get(), rhs.get());

    return Integer<type>(static_cast<type>(static_cast<LhsT>(lhs) % static_cast<RhsT>(rhs)));
}

template <typename LhsT, typename RhsT>
PHI_ALWAYS_INLINE constexpr auto operator%(const LhsT& lhs, const Integer<RhsT>& rhs) noexcept
        -> Integer<detail::integer_result_t<LhsT, RhsT>>
{
    return Integer<LhsT>(lhs) % rhs;
}

template <typename LhsT, typename RhsT>
PHI_ALWAYS_INLINE constexpr auto operator%(const Integer<LhsT>& lhs, const RhsT& rhs) noexcept
        -> Integer<detail::integer_result_t<LhsT, RhsT>>
{
    return lhs % Integer<RhsT>(rhs);
}

template <typename LhsT, typename RhsT, typename = detail::fallback_integer_result<LhsT, RhsT>>
constexpr int operator%(Integer<LhsT>, Integer<RhsT>) = delete;

template <typename LhsT, typename RhsT, typename = detail::fallback_integer_result<LhsT, RhsT>>
constexpr int operator%(LhsT, Integer<RhsT>) = delete;

template <typename LhsT, typename RhsT, typename = detail::fallback_integer_result<LhsT, RhsT>>
constexpr int operator%(Integer<LhsT>, RhsT) = delete;

//=== input/output ===/

template <typename CharT, typename CharTraitsT, typename IntegerT>
std::basic_istream<CharT, CharTraitsT>& operator>>(std::basic_istream<CharT, CharTraitsT>& stream,
                                                   Integer<IntegerT>&                      i)
{
    IntegerT val{IntegerT(0)};
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

//=== Free functions ===/

/// \cond detail
namespace detail
{
    template <typename TypeT>
    struct make_signed
    {
        using type = typename std::make_signed_t<TypeT>;
    };

    template <typename TypeT>
    struct make_signed<Integer<TypeT>>
    {
        using type = Integer<typename std::make_signed_t<TypeT>>;
    };

    template <typename TypeT>
    using make_signed_t = typename make_signed<TypeT>::type;

    template <typename TypeT>
    struct make_unsigned
    {
        using type = typename std::make_unsigned_t<TypeT>;
    };

    template <typename TypeT>
    struct make_unsigned<Integer<TypeT>>
    {
        using type = Integer<typename std::make_unsigned_t<TypeT>>;
    };

    template <typename TypeT>
    using make_unsigned_t = typename make_unsigned<TypeT>::type;
} // namespace detail
/// \endcond

template <typename IntegerT>
using make_signed_t = typename detail::make_signed_t<IntegerT>;

template <typename IntegerT,
          typename = typename std::enable_if_t<detail::is_integer<IntegerT>::value>>
PHI_ALWAYS_INLINE constexpr make_signed_t<IntegerT> make_signed(const IntegerT& val) noexcept
{
    using result_type = make_signed_t<IntegerT>;
    PHI_DBG_ASSERT(val <= std::numeric_limits<result_type>::max(),
                   "Conversion would overflow. Args {}", val);

    return static_cast<result_type>(val);
}

template <typename IntegerT>
PHI_ALWAYS_INLINE constexpr make_signed_t<Integer<IntegerT>> make_signed(
        const Integer<IntegerT>& val) noexcept
{
    return make_signed(static_cast<IntegerT>(val));
}

template <typename IntegerT>
using make_unsigned_t = typename detail::make_unsigned_t<IntegerT>;

template <typename IntegerT,
          typename = typename std::enable_if_t<detail::is_integer<IntegerT>::value>>
PHI_ALWAYS_INLINE constexpr make_unsigned_t<IntegerT> make_unsigned(const IntegerT& val) noexcept
{
    using result_type = make_unsigned_t<IntegerT>;
    PHI_DBG_ASSERT(val >= IntegerT(0), "Conversion would underflow. Arg {}", val);

    return static_cast<result_type>(val);
}

template <typename IntegerT>
PHI_ALWAYS_INLINE constexpr make_unsigned_t<Integer<IntegerT>> make_unsigned(
        const Integer<IntegerT>& val) noexcept
{
    return make_unsigned(static_cast<IntegerT>(val));
}

template <typename SignedIntegerT,
          typename = typename std::enable_if_t<std::is_signed_v<SignedIntegerT>>>
PHI_ALWAYS_INLINE constexpr make_unsigned_t<SignedIntegerT> abs(const SignedIntegerT& val) noexcept
{
    return make_unsigned(val > 0 ? val : -val);
}

template <typename SignedIntegerT,
          typename = typename std::enable_if_t<std::is_signed_v<SignedIntegerT>>>
PHI_ALWAYS_INLINE constexpr make_unsigned_t<Integer<SignedIntegerT>> abs(
        const Integer<SignedIntegerT>& val) noexcept
{
    return make_unsigned(val > 0 ? val : -val);
}

template <typename UnsignedIntegerT,
          typename = typename std::enable_if_t<std::is_unsigned_v<UnsignedIntegerT>>>
PHI_ALWAYS_INLINE constexpr UnsignedIntegerT abs(const UnsignedIntegerT& val) noexcept
{
    return val;
}

template <typename UnsignedIntegerT,
          typename = typename std::enable_if_t<std::is_unsigned_v<UnsignedIntegerT>>>
PHI_ALWAYS_INLINE constexpr Integer<UnsignedIntegerT> abs(
        const Integer<UnsignedIntegerT>& val) noexcept
{
    return val;
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

    template <typename IntegerT>
    struct numeric_limits<phi::Integer<IntegerT>> : std::numeric_limits<IntegerT>
    {};
} // namespace std

#endif // INCG_PHI_UTILITY_INTEGER_HPP
