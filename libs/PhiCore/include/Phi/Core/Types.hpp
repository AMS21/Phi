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

#include "Phi/Core/Boolean.hpp"
#include "Phi/Core/FloatingPoint.hpp"
#include "Phi/Core/Integer.hpp"
#include "Phi/PhiConfig.hpp"
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <type_traits>

DETAIL_PHI_BEGIN_NAMESPACE()

// Integer
using i8  = Integer<std::int8_t>;
using u8  = Integer<std::uint8_t>;
using i16 = Integer<std::int16_t>;
using u16 = Integer<std::uint16_t>;
using i32 = Integer<std::int32_t>;
using u32 = Integer<std::uint32_t>;
using i64 = Integer<std::int64_t>;
using u64 = Integer<std::uint64_t>;

using i8_fast  = Integer<std::int_fast8_t>;
using u8_fast  = Integer<std::uint_fast8_t>;
using i16_fast = Integer<std::int_fast16_t>;
using u16_fast = Integer<std::uint_fast16_t>;
using i32_fast = Integer<std::int_fast32_t>;
using u32_fast = Integer<std::uint_fast32_t>;
using i64_fast = Integer<std::int_fast64_t>;
using u64_fast = Integer<std::uint_fast64_t>;

using i8_least  = Integer<std::int_least8_t>;
using u8_least  = Integer<std::uint_least8_t>;
using i16_least = Integer<std::int_least16_t>;
using u16_least = Integer<std::uint_least16_t>;
using i32_least = Integer<std::int_least32_t>;
using u32_least = Integer<std::uint_least32_t>;
using i64_least = Integer<std::int_least64_t>;
using u64_least = Integer<std::uint_least64_t>;

using isize = Integer<std::make_signed<std::size_t>::type>;
using usize = Integer<std::size_t>;

using ptrdiff = Integer<std::ptrdiff_t>;

// Floating point
using f32 = FloatingPoint<float>;
using f64 = FloatingPoint<double>;

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
    struct conditional_impl<std::true_type, ResultT, TailT...>
    {
        using type = ResultT;
    };

    template <typename ResultT, typename... TailT>
    struct conditional_impl<std::false_type, ResultT, TailT...>
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
            conditional<std::bool_constant<CharT >= '0' && CharT <= '9'>, decimal_digit,
                        std::bool_constant<CharT >= 'a' && CharT <= 'f'>, lower_hexadecimal_digit,
                        std::bool_constant<CharT >= 'A' && CharT <= 'F'>, upper_hexadecimal_digit,
                        no_digit>;

    template <char CharT, typename CatT>
    struct to_digit_impl
    {
        static_assert(!std::is_same<CatT, no_digit>::value, "invalid character, expected digit");
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
    constexpr TypeT to_digit()
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
        static constexpr TypeT parse(TypeT value)
        {
            return value;
        }
    };

    template <char... TailT>
    struct parse_loop<'\'', TailT...>
    {
        template <typename TypeT, TypeT Base>
        static constexpr TypeT parse(TypeT value)
        {
            return parse_loop<TailT...>::template parse<TypeT, Base>(value);
        }
    };

    template <char HeadT, char... TailT>
    struct parse_loop<HeadT, TailT...>
    {
        template <typename TypeT, TypeT Base>
        static constexpr TypeT parse(TypeT value)
        {
            return parse_loop<TailT...>::template parse<TypeT, Base>(
                    value * Base + to_digit<TypeT, Base, HeadT>());
        }
    };

    template <typename TypeT, TypeT Base, char HeadT, char... TailT>
    constexpr TypeT do_parse_loop()
    {
        return parse_loop<TailT...>::template parse<TypeT, Base>(to_digit<TypeT, Base, HeadT>());
    }

    template <typename TypeT, char... DigitsT>
    struct parse_base
    {
        static constexpr TypeT parse()
        {
            return do_parse_loop<TypeT, 10, DigitsT...>();
        }
    };

    template <typename TypeT, char HeadT, char... TailT>
    struct parse_base<TypeT, '0', HeadT, TailT...>
    {
        static constexpr TypeT parse()
        {
            return do_parse_loop<TypeT, 8, HeadT, TailT...>();
        }
    };

    template <typename TypeT, char... TailT>
    struct parse_base<TypeT, '0', 'x', TailT...>
    {
        static constexpr TypeT parse()
        {
            return do_parse_loop<TypeT, 16, TailT...>();
        }
    };

    template <typename TypeT, char... TailT>
    struct parse_base<TypeT, '0', 'X', TailT...>
    {
        static constexpr TypeT parse()
        {
            return do_parse_loop<TypeT, 16, TailT...>();
        }
    };

    template <typename TypeT, char... TailT>
    struct parse_base<TypeT, '0', 'b', TailT...>
    {
        static constexpr TypeT parse()
        {
            return do_parse_loop<TypeT, 2, TailT...>();
        }
    };

    template <typename TypeT, char... TailT>
    struct parse_base<TypeT, '0', 'B', TailT...>
    {
        static constexpr TypeT parse()
        {
            return do_parse_loop<TypeT, 2, TailT...>();
        }
    };

    template <typename TypeT, char... DigitsT>
    constexpr TypeT parse()
    {
        return parse_base<TypeT, DigitsT...>::parse();
    }

    template <typename TypeT, typename OtherT, OtherT Value>
    constexpr TypeT validate_value()
    {
        static_assert(sizeof(TypeT) <= sizeof(OtherT) &&
                              std::is_signed<OtherT>::value == std::is_signed<TypeT>::value,
                      "mismatched types");
        static_assert(OtherT(std::numeric_limits<TypeT>::min()) <= Value &&
                              Value <= OtherT(std::numeric_limits<TypeT>::max()),
                      "integer literal overflow");
        return static_cast<TypeT>(Value);
    }

    template <typename TypeT, char... DigitsT>
    constexpr TypeT parse_signed()
    {
        return validate_value<TypeT, long long, parse<long long, DigitsT...>()>();
    }

    template <typename TypeT, char... DigitsT>
    constexpr TypeT parse_unsigned()
    {
        return validate_value<TypeT, unsigned long long, parse<unsigned long long, DigitsT...>()>();
    }
} // namespace detail

inline namespace literals
{
    template <char... DigitsT>
    constexpr i8 operator"" _i8()
    {
        return i8(detail::parse_signed<std::int8_t, DigitsT...>());
    }

    template <char... DigitsT>
    constexpr u8 operator"" _u8()
    {
        return u8(detail::parse_unsigned<std::uint8_t, DigitsT...>());
    }

    template <char... DigitsT>
    constexpr i16 operator"" _i16()
    {
        return int16_t(detail::parse_signed<std::int16_t, DigitsT...>());
    }

    template <char... DigitsT>
    constexpr u16 operator"" _u16()
    {
        return u16(detail::parse_unsigned<std::uint16_t, DigitsT...>());
    }

    template <char... DigitsT>
    constexpr i32 operator"" _i32()
    {
        return i32(detail::parse_signed<std::int32_t, DigitsT...>());
    }

    template <char... DigitsT>
    constexpr u32 operator"" _u32()
    {
        return u32(detail::parse_unsigned<std::uint32_t, DigitsT...>());
    }

    template <char... DigitsT>
    constexpr i64 operator"" _i64()
    {
        return i64(detail::parse_signed<std::int64_t, DigitsT...>());
    }

    template <char... DigitsT>
    constexpr u64 operator"" _u64()
    {
        return u64(detail::parse_unsigned<std::uint64_t, DigitsT...>());
    }

    template <char... DigitsT>
    constexpr isize operator"" _isize()
    {
        return isize(detail::parse_signed<std::make_signed<std::size_t>::type, DigitsT...>());
    }

    template <char... DigitsT>
    constexpr usize operator"" _usize()
    {
        return usize(detail::parse_unsigned<std::size_t, DigitsT...>());
    }

    constexpr f32 operator"" _f32(long double val)
    {
        return f32(static_cast<std::float_t>(val));
    }

    constexpr f64 operator"" _f64(long double val)
    {
        return f64(static_cast<std::double_t>(val));
    }
} // namespace literals

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPES_HPP
