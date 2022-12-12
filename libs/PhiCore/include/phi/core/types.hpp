// This file is heavily inspired by Jonathan Müllers <jonathanmueller.dev@gmail.com> type_safe library https://github.com/foonathan/type_safe
// licensed under the MIT license https://github.com/foonathan/type_safe/blob/master/LICENSE
// Original files at
// https://github.com/foonathan/type_safe/blob/master/include/type_safe/types.hpp
// https://github.com/foonathan/type_safe/blob/master/include/type_safe/detail/constant_parser.hpp
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
#ifndef INCG_PHI_CORE_TYPES_HPP
#define INCG_PHI_CORE_TYPES_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/consteval.hpp"
#include "phi/compiler_support/warning.hpp"
#include "phi/core/boolean.hpp"
#include "phi/core/floating_point.hpp"
#include "phi/core/integer.hpp"
#include "phi/core/intptr_t.hpp"
#include "phi/core/ptrdiff_t.hpp"
#include "phi/core/size_t.hpp"
#include "phi/core/sized_types.hpp"
#include "phi/type_traits/is_same.hpp"
#include "phi/type_traits/is_signed.hpp"
#include "phi/type_traits/is_unsigned.hpp"
#include "phi/type_traits/make_signed.hpp"
#include <limits>

DETAIL_PHI_BEGIN_NAMESPACE()

// integer
using i8  = integer<int8_t>;
using u8  = integer<uint8_t>;
using i16 = integer<int16_t>;
using u16 = integer<uint16_t>;
using i32 = integer<int32_t>;
using u32 = integer<uint32_t>;
using i64 = integer<int64_t>;
using u64 = integer<uint64_t>;

using i8_fast  = integer<int_fast8_t>;
using u8_fast  = integer<uint_fast8_t>;
using i16_fast = integer<int_fast16_t>;
using u16_fast = integer<uint_fast16_t>;
using i32_fast = integer<int_fast32_t>;
using u32_fast = integer<uint_fast32_t>;
using i64_fast = integer<int_fast64_t>;
using u64_fast = integer<uint_fast64_t>;

using i8_least  = integer<int_least8_t>;
using u8_least  = integer<uint_least8_t>;
using i16_least = integer<int_least16_t>;
using u16_least = integer<uint_least16_t>;
using i32_least = integer<int_least32_t>;
using u32_least = integer<uint_least32_t>;
using i64_least = integer<int_least64_t>;
using u64_least = integer<uint_least64_t>;

using isize = integer<make_signed<size_t>::type>;
using usize = integer<size_t>;

using intptr  = integer<intptr_t>;
using uintptr = integer<uintptr_t>;

using ptrdiff = integer<ptrdiff_t>;

// Floating point
using f32 = floating_point<float32>;
using f64 = floating_point<float64>;

namespace detail
{
    template <typename... TypesT>
    struct conditional_impl;

    template <typename ElseT>
    struct conditional_impl<ElseT>
    {
        using type = ElseT;
    };

    template <typename ResultT, typename... TailT>
    struct conditional_impl<true_type, ResultT, TailT...>
    {
        using type = ResultT;
    };

    template <typename ResultT, typename... TailT>
    struct conditional_impl<false_type, ResultT, TailT...>
    {
        using type = typename conditional_impl<TailT...>::type;
    };

    template <typename... TypesT>
    using conditional = typename conditional_impl<TypesT...>::type;

    struct decimal_digit
    {};

    struct lower_hexadecimal_digit
    {};

    struct upper_hexadecimal_digit
    {};

    struct no_digit
    {};

    template <char CharT>
    using digit_category =
            conditional<bool_constant<CharT >= '0' && CharT <= '9'>, decimal_digit,
                        bool_constant<CharT >= 'a' && CharT <= 'f'>, lower_hexadecimal_digit,
                        bool_constant<CharT >= 'A' && CharT <= 'F'>, upper_hexadecimal_digit,
                        no_digit>;

    template <char CharT, typename CatT>
    struct to_digit_impl
    {
        static_assert(!is_same<CatT, no_digit>::value, "invalid character, expected digit");
    };

    template <char CharT>
    struct to_digit_impl<CharT, decimal_digit>
    {
        static constexpr auto value = static_cast<int>(CharT) - static_cast<int>('0');
    };

    template <char CharT>
    struct to_digit_impl<CharT, lower_hexadecimal_digit>
    {
        static constexpr auto value = static_cast<int>(CharT) - static_cast<int>('a') + 10;
    };

    template <char CharT>
    struct to_digit_impl<CharT, upper_hexadecimal_digit>
    {
        static constexpr auto value = static_cast<int>(CharT) - static_cast<int>('A') + 10;
    };

    template <typename TypeT, TypeT Base, char CharT>
    PHI_CONSTEVAL_OR_CONSTEXPR TypeT to_digit()
    {
        using impl = to_digit_impl<CharT, digit_category<CharT>>;
        static_assert(impl::value < Base, "invalid digit for base");
        return impl::value;
    }

    template <char... DigitsT>
    struct parse_loop;

    template <>
    struct parse_loop<>
    {
        template <typename TypeT, TypeT>
        static PHI_CONSTEVAL_OR_CONSTEXPR TypeT parse(TypeT value)
        {
            return value;
        }
    };

    template <char... TailT>
    struct parse_loop<'\'', TailT...>
    {
        template <typename TypeT, TypeT Base>
        static PHI_CONSTEVAL_OR_CONSTEXPR TypeT parse(TypeT value)
        {
            return parse_loop<TailT...>::template parse<TypeT, Base>(value);
        }
    };

    template <char HeadT, char... TailT>
    struct parse_loop<HeadT, TailT...>
    {
        template <typename TypeT, TypeT Base>
        static PHI_CONSTEVAL_OR_CONSTEXPR TypeT parse(TypeT value)
        {
            return parse_loop<TailT...>::template parse<TypeT, Base>(
                    value * Base + to_digit<TypeT, Base, HeadT>());
        }
    };

    template <typename TypeT, TypeT Base, char HeadT, char... TailT>
    PHI_CONSTEVAL_OR_CONSTEXPR TypeT do_parse_loop()
    {
        return parse_loop<TailT...>::template parse<TypeT, Base>(to_digit<TypeT, Base, HeadT>());
    }

    template <typename TypeT, char... DigitsT>
    struct parse_base
    {
        static PHI_CONSTEVAL_OR_CONSTEXPR TypeT parse()
        {
            return do_parse_loop<TypeT, 10, DigitsT...>();
        }
    };

    template <typename TypeT, char HeadT, char... TailT>
    struct parse_base<TypeT, '0', HeadT, TailT...>
    {
        static PHI_CONSTEVAL_OR_CONSTEXPR TypeT parse()
        {
            return do_parse_loop<TypeT, 8, HeadT, TailT...>();
        }
    };

    template <typename TypeT, char... TailT>
    struct parse_base<TypeT, '0', 'x', TailT...>
    {
        static PHI_CONSTEVAL_OR_CONSTEXPR TypeT parse()
        {
            return do_parse_loop<TypeT, 16, TailT...>();
        }
    };

    template <typename TypeT, char... TailT>
    struct parse_base<TypeT, '0', 'X', TailT...>
    {
        static PHI_CONSTEVAL_OR_CONSTEXPR TypeT parse()
        {
            return do_parse_loop<TypeT, 16, TailT...>();
        }
    };

    template <typename TypeT, char... TailT>
    struct parse_base<TypeT, '0', 'b', TailT...>
    {
        static PHI_CONSTEVAL_OR_CONSTEXPR TypeT parse()
        {
            return do_parse_loop<TypeT, 2, TailT...>();
        }
    };

    template <typename TypeT, char... TailT>
    struct parse_base<TypeT, '0', 'B', TailT...>
    {
        static PHI_CONSTEVAL_OR_CONSTEXPR TypeT parse()
        {
            return do_parse_loop<TypeT, 2, TailT...>();
        }
    };

    template <typename TypeT, char... DigitsT>
    PHI_CONSTEVAL_OR_CONSTEXPR TypeT parse()
    {
        return parse_base<TypeT, DigitsT...>::parse();
    }

    template <typename TypeT, typename OtherT, OtherT Value>
    PHI_CONSTEVAL_OR_CONSTEXPR TypeT validate_value()
    {
        static_assert(sizeof(TypeT) <= sizeof(OtherT) &&
                              is_signed<OtherT>::value == is_signed<TypeT>::value,
                      "mismatched types");
        static_assert(OtherT(std::numeric_limits<TypeT>::min()) <= Value &&
                              Value <= OtherT(std::numeric_limits<TypeT>::max()),
                      "integer literal overflow");
        return static_cast<TypeT>(Value);
    }

    template <typename TypeT, char... DigitsT>
    PHI_CONSTEVAL_OR_CONSTEXPR TypeT parse_signed()
    {
        return validate_value<TypeT, long long, parse<long long, DigitsT...>()>();
    }

    template <typename TypeT, char... DigitsT>
    PHI_CONSTEVAL_OR_CONSTEXPR TypeT parse_unsigned()
    {
        return validate_value<TypeT, unsigned long long, parse<unsigned long long, DigitsT...>()>();
    }
} // namespace detail

PHI_CLANG_SUPPRESS_WARNING_PUSH()
#if PHI_COMPILER_IS_ATLEAST(CLANG, 13, 0, 0)
PHI_CLANG_SUPPRESS_WARNING("-Wreserved-identifier")
#endif

inline namespace literals
{
    template <char... DigitsT>
    PHI_CONSTEVAL_OR_CONSTEXPR i8 operator"" _i8()
    {
        return {detail::parse_signed<int8_t, DigitsT...>()};
    }

    template <char... DigitsT>
    PHI_CONSTEVAL_OR_CONSTEXPR u8 operator"" _u8()
    {
        return {detail::parse_unsigned<uint8_t, DigitsT...>()};
    }

    template <char... DigitsT>
    PHI_CONSTEVAL_OR_CONSTEXPR i16 operator"" _i16()
    {
        return {detail::parse_signed<int16_t, DigitsT...>()};
    }

    template <char... DigitsT>
    PHI_CONSTEVAL_OR_CONSTEXPR u16 operator"" _u16()
    {
        return {detail::parse_unsigned<uint16_t, DigitsT...>()};
    }

    template <char... DigitsT>
    PHI_CONSTEVAL_OR_CONSTEXPR i32 operator"" _i32()
    {
        return {detail::parse_signed<int32_t, DigitsT...>()};
    }

    template <char... DigitsT>
    PHI_CONSTEVAL_OR_CONSTEXPR u32 operator"" _u32()
    {
        return {detail::parse_unsigned<uint32_t, DigitsT...>()};
    }

    template <char... DigitsT>
    PHI_CONSTEVAL_OR_CONSTEXPR i64 operator"" _i64()
    {
        return {detail::parse_signed<int64_t, DigitsT...>()};
    }

    template <char... DigitsT>
    PHI_CONSTEVAL_OR_CONSTEXPR u64 operator"" _u64()
    {
        return {detail::parse_unsigned<uint64_t, DigitsT...>()};
    }

    template <char... DigitsT>
    PHI_CONSTEVAL_OR_CONSTEXPR isize operator"" _isize()
    {
        return {detail::parse_signed<typename make_signed<size_t>::type, DigitsT...>()};
    }

    template <char... DigitsT>
    PHI_CONSTEVAL_OR_CONSTEXPR usize operator"" _usize()
    {
        return {detail::parse_unsigned<size_t, DigitsT...>()};
    }

    PHI_CONSTEVAL_OR_CONSTEXPR f32 operator"" _f32(long double val)
    {
        return {static_cast<float32>(val)};
    }

    PHI_CONSTEVAL_OR_CONSTEXPR f64 operator"" _f64(long double val)
    {
        return {static_cast<float64>(val)};
    }
} // namespace literals

DETAIL_PHI_END_NAMESPACE()

PHI_CLANG_SUPPRESS_WARNING_POP()

#endif // INCG_PHI_CORE_TYPES_HPP
