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

#ifndef INCG_PHI_CORE_INTEGER_HPP
#define INCG_PHI_CORE_INTEGER_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/algorithm/swap.hpp"
#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/inline.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/compiler_support/standard_library.hpp"
#include "phi/compiler_support/warning.hpp"
#include "phi/core/assert.hpp"
#include "phi/core/boolean.hpp"
#include "phi/forward/std/hash.hpp"
#include "phi/type_traits/bool_constant.hpp"
#include "phi/type_traits/conditional.hpp"
#include "phi/type_traits/enable_if.hpp"
#include "phi/type_traits/is_signed.hpp"
#include "phi/type_traits/is_unsafe_integer.hpp"
#include "phi/type_traits/is_unsigned.hpp"
#include <iosfwd>
#include <limits>

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename IntegerT>
class integer;

/// \cond detail
namespace detail
{
    // integer conversion
    template <typename FromT, typename ToT>
    struct is_safe_integer_conversion
        : public bool_constant<is_unsafe_integer<FromT>::value && is_unsafe_integer<ToT>::value &&
                               ((sizeof(FromT) <= sizeof(ToT) &&
                                 is_signed<FromT>::value == is_signed<ToT>::value) ||
                                (sizeof(FromT) < sizeof(ToT) && is_unsigned<FromT>::value &&
                                 is_signed<ToT>::value))>
    {};

    template <typename FromT, typename ToT>
    using enable_safe_integer_conversion =
            enable_if_t<is_safe_integer_conversion<FromT, ToT>::value>;

    template <typename FromT, typename ToT>
    using fallback_safe_integer_conversion =
            enable_if_t<!is_safe_integer_conversion<FromT, ToT>::value>;

    // integer comparison
    template <typename LhsT, typename RhsT>
    struct is_safe_integer_comparison
        : public bool_constant<is_safe_integer_conversion<LhsT, RhsT>::value ||
                               is_safe_integer_conversion<RhsT, LhsT>::value>
    {};

    template <typename LhsT, typename RhsT>
    using enable_safe_integer_comparison =
            enable_if_t<is_safe_integer_comparison<LhsT, RhsT>::value>;

    template <typename LhsT, typename RhsT>
    using fallback_safe_integer_comparison =
            enable_if_t<!is_safe_integer_comparison<LhsT, RhsT>::value>;

    // integer operation
    template <typename LhsT, typename RhsT>
    struct is_safe_integer_operation
        : public bool_constant<is_unsafe_integer<LhsT>::value && is_unsafe_integer<RhsT>::value &&
                               is_signed<LhsT>::value == is_signed<RhsT>::value>
    {};

    template <typename LhsT, typename RhsT>
    struct integer_result_type
        : public enable_if<is_safe_integer_operation<LhsT, RhsT>::value,
                           conditional_t<sizeof(LhsT) < sizeof(RhsT), RhsT, LhsT>>
    {};

    template <typename LhsT, typename RhsT>
    using integer_result_t = typename integer_result_type<LhsT, RhsT>::type;

    template <typename LhsT, typename RhsT>
    using fallback_integer_result =
            enable_if_t<is_unsafe_integer<LhsT>::value && is_unsafe_integer<RhsT>::value &&
                        is_signed<LhsT>::value != is_signed<RhsT>::value>;

    // Error detection
    struct signed_integer_tag
    {};

    struct unsigned_integer_tag
    {};

    template <typename TypeT>
    using arithmetic_tag_for =
            conditional_t<is_signed<TypeT>::value, signed_integer_tag, unsigned_integer_tag>;

    template <typename TypeT>
    PHI_ALWAYS_INLINE constexpr bool will_addition_error(signed_integer_tag /*tag*/, TypeT lhs,
                                                         TypeT rhs) noexcept
    {
        return rhs > TypeT(0) ? lhs > std::numeric_limits<TypeT>::max() - rhs :
                                lhs < std::numeric_limits<TypeT>::min() - rhs;
    }

    template <typename TypeT>
    PHI_ALWAYS_INLINE constexpr bool will_addition_error(unsigned_integer_tag /*tag*/, TypeT lhs,
                                                         TypeT rhs) noexcept
    {
        return std::numeric_limits<TypeT>::max() - rhs < lhs;
    }

    template <typename TypeT>
    PHI_ALWAYS_INLINE constexpr bool will_subtraction_error(signed_integer_tag /*tag*/, TypeT lhs,
                                                            TypeT rhs) noexcept
    {
        return rhs > TypeT(0) ? lhs < std::numeric_limits<TypeT>::min() + rhs :
                                lhs > std::numeric_limits<TypeT>::max() + rhs;
    }

    template <typename TypeT>
    PHI_ALWAYS_INLINE constexpr bool will_subtraction_error(unsigned_integer_tag /*tag*/, TypeT lhs,
                                                            TypeT rhs) noexcept
    {
        return lhs < rhs;
    }

    template <typename TypeT>
    PHI_ALWAYS_INLINE constexpr bool will_multiplication_error(signed_integer_tag /*tag*/,
                                                               TypeT lhs, TypeT rhs) noexcept
    {
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
    PHI_ALWAYS_INLINE constexpr bool will_multiplication_error(unsigned_integer_tag /*tag*/,
                                                               TypeT lhs, TypeT rhs) noexcept
    {
        return rhs != TypeT(0) && lhs > std::numeric_limits<TypeT>::max() / rhs;
    }

    template <typename TypeT>
    PHI_ALWAYS_INLINE constexpr bool will_division_error(signed_integer_tag /*tag*/, TypeT lhs,
                                                         TypeT rhs) noexcept
    {
        return rhs == TypeT(0) || (rhs == TypeT(-1) && lhs == std::numeric_limits<TypeT>::min());
    }

    template <typename TypeT>
    PHI_ALWAYS_INLINE constexpr bool will_division_error(unsigned_integer_tag /*tag*/,
                                                         TypeT /*lhs*/, TypeT rhs) noexcept
    {
        return rhs == TypeT(0);
    }

    template <typename TypeT>
    PHI_ALWAYS_INLINE constexpr bool will_modulo_error(TypeT /*lhs*/, TypeT rhs) noexcept
    {
        return rhs == TypeT(0);
    }
} // namespace detail
/// \endcond

PHI_GCC_SUPPRESS_WARNING_PUSH()
#if PHI_COMPILER_IS_ATLEAST(GCC, 10, 0, 0)
PHI_GCC_SUPPRESS_WARNING("-Warith-conversion")
#else
PHI_GCC_SUPPRESS_WARNING("-Wconversion")
#endif

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
class integer
{
    static_assert(is_unsafe_integer<IntegerT>::value,
                  "[phi::integer] IntegerT must be a real integer type");

public:
    using this_type   = integer<IntegerT>;
    using value_type  = IntegerT;
    using limits_type = std::numeric_limits<IntegerT>;

    //=== constructors ===//

    integer() = delete;

    template <typename TypeT, typename = detail::enable_safe_integer_conversion<TypeT, IntegerT>>
    constexpr integer(const TypeT& val) noexcept
        : m_Value(val)
    {}

    template <typename TypeT, typename = detail::enable_safe_integer_conversion<TypeT, IntegerT>>
    PHI_ALWAYS_INLINE constexpr integer(const integer<TypeT>& val) noexcept
        : m_Value(static_cast<TypeT>(val))
    {}

    template <typename TypeT, typename = detail::fallback_safe_integer_conversion<TypeT, IntegerT>>
    constexpr integer(TypeT) = delete;

    //=== assignment ===//

    template <typename TypeT, typename = detail::enable_safe_integer_conversion<TypeT, IntegerT>>
    PHI_ALWAYS_INLINE PHI_EXTENDED_CONSTEXPR integer& operator=(const TypeT& val) noexcept
    {
        m_Value = val;
        return *this;
    }

    template <typename TypeT, typename = detail::enable_safe_integer_conversion<TypeT, IntegerT>>
    PHI_ALWAYS_INLINE PHI_EXTENDED_CONSTEXPR integer& operator=(const integer<TypeT>& val) noexcept
    {
        m_Value = static_cast<TypeT>(val);
        return *this;
    }

    //=== conversion back ===//

    PHI_NODISCARD PHI_ALWAYS_INLINE explicit constexpr operator IntegerT() const noexcept
    {
        return m_Value;
    }

    PHI_NODISCARD PHI_ALWAYS_INLINE constexpr IntegerT unsafe() const noexcept
    {
        return m_Value;
    }

    PHI_NODISCARD PHI_ALWAYS_INLINE constexpr static integer<IntegerT> min() noexcept
    {
        return limits_type::min();
    }

    PHI_NODISCARD PHI_ALWAYS_INLINE constexpr static integer<IntegerT> max() noexcept
    {
        return limits_type::max();
    }

    PHI_EXTENDED_CONSTEXPR void swap(integer<IntegerT>& other) noexcept
    {
        phi::swap(m_Value, other.m_Value);
    }

    //=== unary operators ===//
    PHI_ALWAYS_INLINE constexpr integer operator+() const noexcept
    {
        return *this;
    }

    PHI_ALWAYS_INLINE PHI_EXTENDED_CONSTEXPR integer operator-() const noexcept
    {
        static_assert(is_signed<IntegerT>::value, "Cannot call unary minus on unsigned integer");

        PHI_ASSERT(m_Value != limits_type::min(), "Unary minus will overflow. Args {}", m_Value);

        return integer(-m_Value);
    }

    PHI_ALWAYS_INLINE PHI_EXTENDED_CONSTEXPR integer& operator++() noexcept
    {
        PHI_ASSERT(!detail::will_addition_error(detail::arithmetic_tag_for<IntegerT>{}, m_Value,
                                                IntegerT(1)),
                   "Operator++ will result in overflow. Args {}", m_Value);

        m_Value += 1;
        return *this;
    }

    // cppcheck-suppress functionConst; NOLINTNEXTLINE(readability-const-return-type)
    PHI_ALWAYS_INLINE PHI_EXTENDED_CONSTEXPR const integer operator++(int) noexcept
    {
        auto res = *this;
        ++*this;
        return res;
    }

    PHI_ALWAYS_INLINE PHI_EXTENDED_CONSTEXPR integer& operator--() noexcept
    {
        PHI_ASSERT(!detail::will_subtraction_error(detail::arithmetic_tag_for<IntegerT>{}, m_Value,
                                                   IntegerT(1)),
                   "Operator-- will result in underflow. Args {}", m_Value);

        m_Value -= 1;
        return *this;
    }

    // cppcheck-suppress functionConst; NOLINTNEXTLINE(readability-const-return-type)
    PHI_ALWAYS_INLINE PHI_EXTENDED_CONSTEXPR const integer operator--(int) noexcept
    {
        auto res = *this;
        --*this;
        return res;
    }

    //=== compound assignment ====//

    template <typename TypeT, typename = detail::enable_safe_integer_conversion<TypeT, IntegerT>>
    PHI_ALWAYS_INLINE PHI_EXTENDED_CONSTEXPR integer& operator+=(
            const integer<TypeT>& other) noexcept
    {
        PHI_ASSERT(!detail::will_addition_error<IntegerT>(detail::arithmetic_tag_for<IntegerT>{},
                                                          m_Value, other.unsafe()),
                   "Addition will result in overflow. Args {} + {}", m_Value, other.unsafe());

        m_Value += other.unsafe();
        return *this;
    }

    template <typename TypeT, typename = detail::enable_safe_integer_conversion<TypeT, IntegerT>>
    PHI_ALWAYS_INLINE PHI_EXTENDED_CONSTEXPR integer& operator+=(const TypeT& other) noexcept
    {
        return *this += integer<TypeT>(other);
    }

    template <typename TypeT, typename = detail::fallback_safe_integer_conversion<TypeT, IntegerT>>
    integer& operator+=(integer<TypeT>) = delete;

    template <typename TypeT, typename = detail::fallback_safe_integer_conversion<TypeT, IntegerT>>
    integer& operator+=(TypeT) = delete;

    template <typename TypeT, typename = detail::enable_safe_integer_conversion<TypeT, IntegerT>>
    PHI_ALWAYS_INLINE PHI_EXTENDED_CONSTEXPR integer& operator-=(
            const integer<TypeT>& other) noexcept
    {
        PHI_ASSERT(!detail::will_subtraction_error<IntegerT>(detail::arithmetic_tag_for<IntegerT>{},
                                                             m_Value, other.unsafe()),
                   "Subtraction will result in underflow. Args {} - {}", m_Value, other.unsafe());

        m_Value -= other.unsafe();
        return *this;
    }

    template <typename TypeT, typename = detail::enable_safe_integer_conversion<TypeT, IntegerT>>
    PHI_ALWAYS_INLINE PHI_EXTENDED_CONSTEXPR integer& operator-=(const TypeT& other) noexcept
    {
        return *this -= integer<TypeT>(other);
    }

    template <typename TypeT, typename = detail::fallback_safe_integer_conversion<TypeT, IntegerT>>
    integer& operator-=(integer<TypeT>) = delete;

    template <typename TypeT, typename = detail::fallback_safe_integer_conversion<TypeT, IntegerT>>
    integer& operator-=(TypeT) = delete;

    template <typename TypeT, typename = detail::enable_safe_integer_conversion<TypeT, IntegerT>>
    PHI_ALWAYS_INLINE PHI_EXTENDED_CONSTEXPR integer& operator*=(
            const integer<TypeT>& other) noexcept
    {
        PHI_ASSERT(!detail::will_multiplication_error<IntegerT>(
                           detail::arithmetic_tag_for<IntegerT>{}, m_Value, other.unsafe()),
                   "Multiplication will result in overflow. Args {} * {}", m_Value, other.unsafe());

        m_Value *= other.unsafe();
        return *this;
    }

    template <typename TypeT, typename = detail::enable_safe_integer_conversion<TypeT, IntegerT>>
    PHI_ALWAYS_INLINE PHI_EXTENDED_CONSTEXPR integer& operator*=(const TypeT& other) noexcept
    {
        return *this *= integer<TypeT>(other);
    }

    template <typename TypeT, typename = detail::fallback_safe_integer_conversion<TypeT, IntegerT>>
    integer& operator*=(integer<TypeT>) = delete;

    template <typename TypeT, typename = detail::fallback_safe_integer_conversion<TypeT, IntegerT>>
    integer& operator*=(TypeT) = delete;

    template <typename TypeT, typename = detail::enable_safe_integer_conversion<TypeT, IntegerT>>
    PHI_ALWAYS_INLINE PHI_EXTENDED_CONSTEXPR integer& operator/=(
            const integer<TypeT>& other) noexcept
    {
        PHI_ASSERT(!detail::will_division_error<IntegerT>(detail::arithmetic_tag_for<IntegerT>{},
                                                          m_Value, other.unsafe()),
                   "Division error. Args {} / {}", m_Value, other.unsafe());

        m_Value /= other.unsafe();
        return *this;
    }

    template <typename TypeT, typename = detail::enable_safe_integer_conversion<TypeT, IntegerT>>
    PHI_ALWAYS_INLINE PHI_EXTENDED_CONSTEXPR integer& operator/=(const TypeT& other) noexcept
    {
        return *this /= integer<TypeT>(other);
    }

    template <typename TypeT, typename = detail::fallback_safe_integer_conversion<TypeT, IntegerT>>
    integer& operator/=(integer<TypeT>) = delete;

    template <typename TypeT, typename = detail::fallback_safe_integer_conversion<TypeT, IntegerT>>
    integer& operator/=(TypeT) = delete;

    template <typename TypeT, typename = detail::enable_safe_integer_conversion<TypeT, IntegerT>>
    PHI_ALWAYS_INLINE PHI_EXTENDED_CONSTEXPR integer& operator%=(
            const integer<TypeT>& other) noexcept
    {
        PHI_ASSERT(!detail::will_modulo_error<IntegerT>(m_Value, other.unsafe()),
                   "Modulo error. Args {} % {}", m_Value, other.unsafe());

        m_Value %= other.unsafe();
        return *this;
    }

    template <typename TypeT, typename = detail::enable_safe_integer_conversion<TypeT, IntegerT>>
    PHI_ALWAYS_INLINE PHI_EXTENDED_CONSTEXPR integer& operator%=(const TypeT& other) noexcept
    {
        return *this %= integer<TypeT>(other);
    }

    template <typename TypeT, typename = detail::fallback_safe_integer_conversion<TypeT, IntegerT>>
    integer& operator%=(integer<TypeT>) = delete;

    template <typename TypeT, typename = detail::fallback_safe_integer_conversion<TypeT, IntegerT>>
    integer& operator%=(TypeT) = delete;

private:
    IntegerT m_Value;
};

PHI_GCC_SUPPRESS_WARNING_POP()

//=== comparison ===//

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_integer_comparison<LhsT, RhsT>>
PHI_ALWAYS_INLINE constexpr boolean operator==(const integer<LhsT>& lhs,
                                               const integer<RhsT>& rhs) noexcept
{
    return static_cast<LhsT>(lhs) == static_cast<RhsT>(rhs);
}

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_integer_comparison<LhsT, RhsT>>
PHI_ALWAYS_INLINE constexpr boolean operator==(const LhsT& lhs, const integer<RhsT>& rhs) noexcept
{
    return integer<LhsT>(lhs) == rhs;
}

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_integer_comparison<LhsT, RhsT>>
PHI_ALWAYS_INLINE constexpr boolean operator==(const integer<LhsT>& lhs, const RhsT& rhs) noexcept
{
    return lhs == integer<RhsT>(rhs);
}

template <typename LhsT, typename RhsT,
          typename = detail::fallback_safe_integer_comparison<LhsT, RhsT>>
constexpr boolean operator==(integer<LhsT>, integer<RhsT>) = delete;

template <typename LhsT, typename RhsT,
          typename = detail::fallback_safe_integer_comparison<LhsT, RhsT>>
constexpr boolean operator==(LhsT, integer<RhsT>) = delete;

template <typename LhsT, typename RhsT,
          typename = detail::fallback_safe_integer_comparison<LhsT, RhsT>>
constexpr boolean operator==(integer<LhsT>, RhsT) = delete;

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_integer_comparison<LhsT, RhsT>>
PHI_ALWAYS_INLINE constexpr boolean operator!=(const integer<LhsT>& lhs,
                                               const integer<RhsT>& rhs) noexcept
{
    return static_cast<LhsT>(lhs) != static_cast<RhsT>(rhs);
}

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_integer_comparison<LhsT, RhsT>>
PHI_ALWAYS_INLINE constexpr boolean operator!=(const LhsT& lhs, const integer<RhsT>& rhs) noexcept
{
    return integer<LhsT>(lhs) != rhs;
}

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_integer_comparison<LhsT, RhsT>>
PHI_ALWAYS_INLINE constexpr boolean operator!=(const integer<LhsT>& lhs, const RhsT& rhs) noexcept
{
    return lhs != integer<RhsT>(rhs);
}

template <typename LhsT, typename RhsT,
          typename = detail::fallback_safe_integer_comparison<LhsT, RhsT>>
constexpr boolean operator!=(integer<LhsT>, integer<RhsT>) = delete;

template <typename LhsT, typename RhsT,
          typename = detail::fallback_safe_integer_comparison<LhsT, RhsT>>
constexpr boolean operator!=(LhsT, integer<RhsT>) = delete;

template <typename LhsT, typename RhsT,
          typename = detail::fallback_safe_integer_comparison<LhsT, RhsT>>
constexpr boolean operator!=(integer<LhsT>, RhsT) = delete;

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_integer_comparison<LhsT, RhsT>>
PHI_ALWAYS_INLINE constexpr boolean operator<(const integer<LhsT>& lhs,
                                              const integer<RhsT>& rhs) noexcept
{
    return static_cast<LhsT>(lhs) < static_cast<RhsT>(rhs);
}

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_integer_comparison<LhsT, RhsT>>
PHI_ALWAYS_INLINE constexpr boolean operator<(const LhsT& lhs, const integer<RhsT>& rhs) noexcept
{
    return integer<LhsT>(lhs) < rhs;
}

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_integer_comparison<LhsT, RhsT>>
PHI_ALWAYS_INLINE constexpr boolean operator<(const integer<LhsT>& lhs, const RhsT& rhs) noexcept
{
    return lhs < integer<RhsT>(rhs);
}

template <typename LhsT, typename RhsT,
          typename = detail::fallback_safe_integer_comparison<LhsT, RhsT>>
constexpr boolean operator<(integer<LhsT>, integer<RhsT>) = delete;

template <typename LhsT, typename RhsT,
          typename = detail::fallback_safe_integer_comparison<LhsT, RhsT>>
constexpr boolean operator<(LhsT, integer<RhsT>) = delete;

template <typename LhsT, typename RhsT,
          typename = detail::fallback_safe_integer_comparison<LhsT, RhsT>>
constexpr boolean operator<(integer<LhsT>, RhsT) = delete;

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_integer_comparison<LhsT, RhsT>>
PHI_ALWAYS_INLINE constexpr boolean operator<=(const integer<LhsT>& lhs,
                                               const integer<RhsT>& rhs) noexcept
{
    return static_cast<LhsT>(lhs) <= static_cast<RhsT>(rhs);
}

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_integer_comparison<LhsT, RhsT>>
PHI_ALWAYS_INLINE constexpr boolean operator<=(const LhsT& lhs, const integer<RhsT>& rhs) noexcept
{
    return integer<LhsT>(lhs) <= rhs;
}

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_integer_comparison<LhsT, RhsT>>
PHI_ALWAYS_INLINE constexpr boolean operator<=(const integer<LhsT>& lhs, const RhsT& rhs) noexcept
{
    return lhs <= integer<RhsT>(rhs);
}

template <typename LhsT, typename RhsT,
          typename = detail::fallback_safe_integer_comparison<LhsT, RhsT>>
constexpr boolean operator<=(integer<LhsT>, integer<RhsT>) = delete;

template <typename LhsT, typename RhsT,
          typename = detail::fallback_safe_integer_comparison<LhsT, RhsT>>
constexpr boolean operator<=(LhsT, integer<RhsT>) = delete;

template <typename LhsT, typename RhsT,
          typename = detail::fallback_safe_integer_comparison<LhsT, RhsT>>
constexpr boolean operator<=(integer<LhsT>, RhsT) = delete;

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_integer_comparison<LhsT, RhsT>>
PHI_ALWAYS_INLINE constexpr boolean operator>(const integer<LhsT>& lhs,
                                              const integer<RhsT>& rhs) noexcept
{
    return static_cast<LhsT>(lhs) > static_cast<RhsT>(rhs);
}

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_integer_comparison<LhsT, RhsT>>
PHI_ALWAYS_INLINE constexpr boolean operator>(const LhsT& lhs, const integer<RhsT>& rhs) noexcept
{
    return integer<LhsT>(lhs) > rhs;
}

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_integer_comparison<LhsT, RhsT>>
PHI_ALWAYS_INLINE constexpr boolean operator>(const integer<LhsT>& lhs, const RhsT& rhs) noexcept
{
    return lhs > integer<RhsT>(rhs);
}

template <typename LhsT, typename RhsT,
          typename = detail::fallback_safe_integer_comparison<LhsT, RhsT>>
constexpr boolean operator>(integer<LhsT>, integer<RhsT>) = delete;

template <typename LhsT, typename RhsT,
          typename = detail::fallback_safe_integer_comparison<LhsT, RhsT>>
constexpr boolean operator>(LhsT, integer<RhsT>) = delete;

template <typename LhsT, typename RhsT,
          typename = detail::fallback_safe_integer_comparison<LhsT, RhsT>>
constexpr boolean operator>(integer<LhsT>, RhsT) = delete;

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_integer_comparison<LhsT, RhsT>>
PHI_ALWAYS_INLINE constexpr boolean operator>=(const integer<LhsT>& lhs,
                                               const integer<RhsT>& rhs) noexcept
{
    return static_cast<LhsT>(lhs) >= static_cast<RhsT>(rhs);
}

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_integer_comparison<LhsT, RhsT>>
PHI_ALWAYS_INLINE constexpr boolean operator>=(const LhsT& lhs, const integer<RhsT>& rhs) noexcept
{
    return integer<LhsT>(lhs) >= rhs;
}

template <typename LhsT, typename RhsT,
          typename = detail::enable_safe_integer_comparison<LhsT, RhsT>>
PHI_ALWAYS_INLINE constexpr boolean operator>=(const integer<LhsT>& lhs, const RhsT& rhs) noexcept
{
    return lhs >= integer<RhsT>(rhs);
}

template <typename LhsT, typename RhsT,
          typename = detail::fallback_safe_integer_comparison<LhsT, RhsT>>
constexpr boolean operator>=(integer<LhsT>, integer<RhsT>) = delete;

template <typename LhsT, typename RhsT,
          typename = detail::fallback_safe_integer_comparison<LhsT, RhsT>>
constexpr boolean operator>=(LhsT, integer<RhsT>) = delete;

template <typename LhsT, typename RhsT,
          typename = detail::fallback_safe_integer_comparison<LhsT, RhsT>>
constexpr boolean operator>=(integer<LhsT>, RhsT) = delete;

//=== binary operations ===//

template <typename LhsT, typename RhsT>
PHI_ALWAYS_INLINE PHI_EXTENDED_CONSTEXPR auto operator+(const integer<LhsT>& lhs,
                                                        const integer<RhsT>& rhs) noexcept
        -> integer<detail::integer_result_t<LhsT, RhsT>>
{
    using type = detail::integer_result_t<LhsT, RhsT>;
    PHI_ASSERT(!detail::will_addition_error(detail::arithmetic_tag_for<type>{},
                                            static_cast<type>(lhs.unsafe()),
                                            static_cast<type>(rhs.unsafe())),
               "Addition will result in overflow. Args {} + {}", lhs.unsafe(), rhs.unsafe());

    return integer<type>(static_cast<type>(static_cast<LhsT>(lhs) + static_cast<RhsT>(rhs)));
}

template <typename LhsT, typename RhsT>
PHI_ALWAYS_INLINE constexpr auto operator+(const LhsT& lhs, const integer<RhsT>& rhs) noexcept
        -> integer<detail::integer_result_t<LhsT, RhsT>>
{
    return integer<LhsT>(lhs) + rhs;
}

template <typename LhsT, typename RhsT>
PHI_ALWAYS_INLINE constexpr auto operator+(const integer<LhsT>& lhs, const RhsT& rhs) noexcept
        -> integer<detail::integer_result_t<LhsT, RhsT>>
{
    return lhs + integer<RhsT>(rhs);
}

template <typename LhsT, typename RhsT, typename = detail::fallback_integer_result<LhsT, RhsT>>
constexpr int operator+(integer<LhsT>, integer<RhsT>) = delete;

template <typename LhsT, typename RhsT, typename = detail::fallback_integer_result<LhsT, RhsT>>
constexpr int operator+(LhsT, integer<RhsT>) = delete;

template <typename LhsT, typename RhsT, typename = detail::fallback_integer_result<LhsT, RhsT>>
constexpr int operator+(integer<LhsT>, RhsT) = delete;

template <typename LhsT, typename RhsT>
PHI_ALWAYS_INLINE PHI_EXTENDED_CONSTEXPR auto operator-(const integer<LhsT>& lhs,
                                                        const integer<RhsT>& rhs) noexcept
        -> integer<detail::integer_result_t<LhsT, RhsT>>
{
    using type = detail::integer_result_t<LhsT, RhsT>;
    PHI_ASSERT(!detail::will_subtraction_error(detail::arithmetic_tag_for<type>{},
                                               static_cast<type>(lhs.unsafe()),
                                               static_cast<type>(rhs.unsafe())),
               "Subtraction will result in underflow. Args {} - {}", lhs.unsafe(), rhs.unsafe());

    return integer<type>(static_cast<type>(static_cast<LhsT>(lhs) - static_cast<RhsT>(rhs)));
}

template <typename LhsT, typename RhsT>
PHI_ALWAYS_INLINE constexpr auto operator-(const LhsT& lhs, const integer<RhsT>& rhs) noexcept
        -> integer<detail::integer_result_t<LhsT, RhsT>>
{
    return integer<LhsT>(lhs) - rhs;
}

template <typename LhsT, typename RhsT>
PHI_ALWAYS_INLINE constexpr auto operator-(const integer<LhsT>& lhs, const RhsT& rhs) noexcept
        -> integer<detail::integer_result_t<LhsT, RhsT>>
{
    return lhs - integer<RhsT>(rhs);
}

template <typename LhsT, typename RhsT, typename = detail::fallback_integer_result<LhsT, RhsT>>
constexpr int operator-(integer<LhsT>, integer<RhsT>) = delete;

template <typename LhsT, typename RhsT, typename = detail::fallback_integer_result<LhsT, RhsT>>
constexpr int operator-(LhsT, integer<RhsT>) = delete;

template <typename LhsT, typename RhsT, typename = detail::fallback_integer_result<LhsT, RhsT>>
constexpr int operator-(integer<LhsT>, RhsT) = delete;

template <typename LhsT, typename RhsT>
PHI_ALWAYS_INLINE PHI_EXTENDED_CONSTEXPR auto operator*(const integer<LhsT>& lhs,
                                                        const integer<RhsT>& rhs) noexcept
        -> integer<detail::integer_result_t<LhsT, RhsT>>
{
    using type = detail::integer_result_t<LhsT, RhsT>;
    PHI_ASSERT(!detail::will_multiplication_error(detail::arithmetic_tag_for<type>{},
                                                  static_cast<type>(lhs.unsafe()),
                                                  static_cast<type>(rhs.unsafe())),
               "Multiplication will result in overflow. Args {} * {}", lhs.unsafe(), rhs.unsafe());

    return integer<type>(static_cast<type>(static_cast<LhsT>(lhs) * static_cast<RhsT>(rhs)));
}

template <typename LhsT, typename RhsT>
PHI_ALWAYS_INLINE constexpr auto operator*(const LhsT& lhs, const integer<RhsT>& rhs) noexcept
        -> integer<detail::integer_result_t<LhsT, RhsT>>
{
    return integer<LhsT>(lhs) * rhs;
}

template <typename LhsT, typename RhsT>
PHI_ALWAYS_INLINE constexpr auto operator*(const integer<LhsT>& lhs, const RhsT& rhs) noexcept
        -> integer<detail::integer_result_t<LhsT, RhsT>>
{
    return lhs * integer<RhsT>(rhs);
}

template <typename LhsT, typename RhsT, typename = detail::fallback_integer_result<LhsT, RhsT>>
constexpr int operator*(integer<LhsT>, integer<RhsT>) = delete;

template <typename LhsT, typename RhsT, typename = detail::fallback_integer_result<LhsT, RhsT>>
constexpr int operator*(LhsT, integer<RhsT>) = delete;

template <typename LhsT, typename RhsT, typename = detail::fallback_integer_result<LhsT, RhsT>>
constexpr int operator*(integer<LhsT>, RhsT) = delete;

template <typename LhsT, typename RhsT>
PHI_ALWAYS_INLINE PHI_EXTENDED_CONSTEXPR auto operator/(const integer<LhsT>& lhs,
                                                        const integer<RhsT>& rhs) noexcept
        -> integer<detail::integer_result_t<LhsT, RhsT>>
{
    using type = detail::integer_result_t<LhsT, RhsT>;
    PHI_ASSERT(!detail::will_division_error(detail::arithmetic_tag_for<type>{},
                                            static_cast<type>(lhs.unsafe()),
                                            static_cast<type>(rhs.unsafe())),
               "Division by zero/overflow. Args {} / {}", lhs.unsafe(), rhs.unsafe());

    return integer<type>(static_cast<type>(static_cast<LhsT>(lhs) / static_cast<RhsT>(rhs)));
}

template <typename LhsT, typename RhsT>
PHI_ALWAYS_INLINE constexpr auto operator/(const LhsT& lhs, const integer<RhsT>& rhs) noexcept
        -> integer<detail::integer_result_t<LhsT, RhsT>>
{
    return integer<LhsT>(lhs) / rhs;
}

template <typename LhsT, typename RhsT>
PHI_ALWAYS_INLINE constexpr auto operator/(const integer<LhsT>& lhs, const RhsT& rhs) noexcept
        -> integer<detail::integer_result_t<LhsT, RhsT>>
{
    return lhs / integer<RhsT>(rhs);
}

template <typename LhsT, typename RhsT, typename = detail::fallback_integer_result<LhsT, RhsT>>
constexpr int operator/(integer<LhsT>, integer<RhsT>) = delete;

template <typename LhsT, typename RhsT, typename = detail::fallback_integer_result<LhsT, RhsT>>
constexpr int operator/(LhsT, integer<RhsT>) = delete;

template <typename LhsT, typename RhsT, typename = detail::fallback_integer_result<LhsT, RhsT>>
constexpr int operator/(integer<LhsT>, RhsT) = delete;

template <typename LhsT, typename RhsT>
PHI_ALWAYS_INLINE PHI_EXTENDED_CONSTEXPR auto operator%(const integer<LhsT>& lhs,
                                                        const integer<RhsT>& rhs) noexcept
        -> integer<detail::integer_result_t<LhsT, RhsT>>
{
    using type = detail::integer_result_t<LhsT, RhsT>;
    PHI_ASSERT(!detail::will_modulo_error(static_cast<type>(lhs.unsafe()),
                                          static_cast<type>(rhs.unsafe())),
               "Modulo by zero. Args {} % {}", lhs.unsafe(), rhs.unsafe());

    return integer<type>(static_cast<type>(static_cast<LhsT>(lhs) % static_cast<RhsT>(rhs)));
}

template <typename LhsT, typename RhsT>
PHI_ALWAYS_INLINE constexpr auto operator%(const LhsT& lhs, const integer<RhsT>& rhs) noexcept
        -> integer<detail::integer_result_t<LhsT, RhsT>>
{
    return integer<LhsT>(lhs) % rhs;
}

template <typename LhsT, typename RhsT>
PHI_ALWAYS_INLINE constexpr auto operator%(const integer<LhsT>& lhs, const RhsT& rhs) noexcept
        -> integer<detail::integer_result_t<LhsT, RhsT>>
{
    return lhs % integer<RhsT>(rhs);
}

template <typename LhsT, typename RhsT, typename = detail::fallback_integer_result<LhsT, RhsT>>
constexpr int operator%(integer<LhsT>, integer<RhsT>) = delete;

template <typename LhsT, typename RhsT, typename = detail::fallback_integer_result<LhsT, RhsT>>
constexpr int operator%(LhsT, integer<RhsT>) = delete;

template <typename LhsT, typename RhsT, typename = detail::fallback_integer_result<LhsT, RhsT>>
constexpr int operator%(integer<LhsT>, RhsT) = delete;

//=== input/output ===/

template <typename CharT, typename CharTraitsT, typename IntegerT>
std::basic_istream<CharT, CharTraitsT>& operator>>(std::basic_istream<CharT, CharTraitsT>& stream,
                                                   integer<IntegerT>&                      integer)
{
    IntegerT val{IntegerT(0)};
    stream >> val;
    integer = val;
    return stream;
}

template <typename CharT, typename CharTraitsT, typename IntegerT>
std::basic_ostream<CharT, CharTraitsT>& operator<<(std::basic_ostream<CharT, CharTraitsT>& stream,
                                                   const integer<IntegerT>&                val)
{
    return stream << static_cast<IntegerT>(val);
}

template <typename IntegerT>
PHI_EXTENDED_CONSTEXPR_OR_INLINE void swap(integer<IntegerT>& lhs, integer<IntegerT>& rhs) noexcept
{
    lhs.swap(rhs);
}

DETAIL_PHI_END_NAMESPACE()

DETAIL_PHI_BEGIN_STD_NAMESPACE()

/// Hash specialization for [phi::integer].
template <typename IntegerT>
struct hash<phi::integer<IntegerT>>
{
    phi::size_t operator()(const phi::integer<IntegerT>& val) const noexcept
    {
        return std::hash<IntegerT>()(static_cast<IntegerT>(val));
    }
};

template <typename IntegerT>
struct numeric_limits<phi::integer<IntegerT>> : public std::numeric_limits<IntegerT>
{};

DETAIL_PHI_END_STD_NAMESPACE()

#endif // INCG_PHI_CORE_INTEGER_HPP
