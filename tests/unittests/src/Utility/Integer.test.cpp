// This file is heavily inspired by Jonathan Müllers <jonathanmueller.dev@gmail.com> type_safe library https://github.com/foonathan/type_safe
// licensed under the MIT license https://github.com/foonathan/type_safe/blob/master/LICENSE
// Original file at https://github.com/foonathan/type_safe/blob/master/test/integer.cpp
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

#include "ConstexprHelper.hpp"
#include <Phi/Utility/Integer.hpp>
#include <catch2/catch.hpp>
#include <cpp/Warning.hpp>
#include <cstdint>
#include <sstream>
#include <string>
#include <type_traits>

#define TEST_CONVERSION(lhs, rhs)                                                                  \
    (std::is_constructible_v<lhs, rhs> && std::is_nothrow_constructible_v<lhs, rhs> &&             \
     std::is_assignable_v<lhs, rhs> && std::is_nothrow_assignable_v<lhs, rhs> &&                   \
     (std::is_constructible_v<rhs, lhs> == std::is_same_v<lhs::value_type, rhs> &&                 \
      std::is_nothrow_constructible_v<rhs, lhs> == std::is_same_v<lhs::value_type, rhs>))

CPP_GCC_SUPPRESS_WARNING_PUSH
CPP_GCC_SUPPRESS_WARNING("-Wuseless-cast")

TEST_CASE("Integer layout", "[Utility][Types][Integer]")
{
    STATIC_REQUIRE(sizeof(phi::Integer<std::int8_t>) == sizeof(std::int8_t));
    STATIC_REQUIRE(sizeof(phi::Integer<std::int16_t>) == sizeof(std::int16_t));
    STATIC_REQUIRE(sizeof(phi::Integer<std::int32_t>) == sizeof(std::int32_t));
    STATIC_REQUIRE(sizeof(phi::Integer<std::int64_t>) == sizeof(std::int64_t));
    STATIC_REQUIRE(sizeof(phi::Integer<std::uint8_t>) == sizeof(std::uint8_t));
    STATIC_REQUIRE(sizeof(phi::Integer<std::uint16_t>) == sizeof(std::uint16_t));
    STATIC_REQUIRE(sizeof(phi::Integer<std::uint32_t>) == sizeof(std::uint32_t));
    STATIC_REQUIRE(sizeof(phi::Integer<std::uint64_t>) == sizeof(std::uint64_t));

    STATIC_REQUIRE(std::is_standard_layout_v<phi::Integer<std::int32_t>>);
    STATIC_REQUIRE(std::is_trivially_copyable_v<phi::Integer<std::int32_t>>);
    STATIC_REQUIRE_FALSE(std::is_default_constructible_v<phi::Integer<std::int32_t>>);
}

TEST_CASE("Integer conversion checks", "[Utility][Types][Integer]")
{
    // std::int8_t
    STATIC_REQUIRE(TEST_CONVERSION(phi::Integer<std::int8_t>, std::int8_t));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::int8_t>, std::int16_t));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::int8_t>, std::int32_t));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::int8_t>, std::int64_t));

    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::int8_t>, std::uint8_t));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::int8_t>, std::uint16_t));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::int8_t>, std::uint32_t));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::int8_t>, std::uint64_t));

    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::int8_t>, bool));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::int8_t>, char));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::int8_t>, wchar_t));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::int8_t>, char16_t));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::int8_t>, char32_t));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::int8_t>, float));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::int8_t>, double));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::int8_t>, long double));

    // std::int16_t
    STATIC_REQUIRE(TEST_CONVERSION(phi::Integer<std::int16_t>, std::int8_t));
    STATIC_REQUIRE(TEST_CONVERSION(phi::Integer<std::int16_t>, std::int16_t));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::int16_t>, std::int32_t));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::int16_t>, std::int64_t));

    STATIC_REQUIRE(TEST_CONVERSION(phi::Integer<std::int16_t>, std::uint8_t));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::int16_t>, std::uint16_t));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::int16_t>, std::uint32_t));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::int16_t>, std::uint64_t));

    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::int16_t>, bool));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::int16_t>, char));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::int16_t>, wchar_t));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::int16_t>, char16_t));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::int16_t>, char32_t));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::int16_t>, float));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::int16_t>, double));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::int16_t>, long double));

    // std::int32_t
    STATIC_REQUIRE(TEST_CONVERSION(phi::Integer<std::int32_t>, std::int8_t));
    STATIC_REQUIRE(TEST_CONVERSION(phi::Integer<std::int32_t>, std::int16_t));
    STATIC_REQUIRE(TEST_CONVERSION(phi::Integer<std::int32_t>, std::int32_t));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::int32_t>, std::int64_t));

    STATIC_REQUIRE(TEST_CONVERSION(phi::Integer<std::int32_t>, std::uint8_t));
    STATIC_REQUIRE(TEST_CONVERSION(phi::Integer<std::int32_t>, std::uint16_t));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::int32_t>, std::uint32_t));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::int32_t>, std::uint64_t));

    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::int32_t>, bool));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::int32_t>, char));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::int32_t>, wchar_t));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::int32_t>, char16_t));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::int32_t>, char32_t));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::int32_t>, float));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::int32_t>, double));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::int32_t>, long double));

    // std::int64_t
    STATIC_REQUIRE(TEST_CONVERSION(phi::Integer<std::int64_t>, std::int8_t));
    STATIC_REQUIRE(TEST_CONVERSION(phi::Integer<std::int64_t>, std::int16_t));
    STATIC_REQUIRE(TEST_CONVERSION(phi::Integer<std::int64_t>, std::int32_t));
    STATIC_REQUIRE(TEST_CONVERSION(phi::Integer<std::int64_t>, std::int64_t));

    STATIC_REQUIRE(TEST_CONVERSION(phi::Integer<std::int64_t>, std::uint8_t));
    STATIC_REQUIRE(TEST_CONVERSION(phi::Integer<std::int64_t>, std::uint16_t));
    STATIC_REQUIRE(TEST_CONVERSION(phi::Integer<std::int64_t>, std::uint32_t));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::int64_t>, std::uint64_t));

    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::int64_t>, bool));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::int64_t>, char));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::int64_t>, wchar_t));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::int64_t>, char16_t));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::int64_t>, char32_t));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::int64_t>, float));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::int64_t>, double));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::int64_t>, long double));

    // std::uint8_t
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::uint8_t>, std::int8_t));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::uint8_t>, std::int16_t));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::uint8_t>, std::int32_t));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::uint8_t>, std::int64_t));

    STATIC_REQUIRE(TEST_CONVERSION(phi::Integer<std::uint8_t>, std::uint8_t));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::uint8_t>, std::uint16_t));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::uint8_t>, std::uint32_t));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::uint8_t>, std::uint64_t));

    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::uint8_t>, bool));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::uint8_t>, char));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::uint8_t>, wchar_t));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::uint8_t>, char16_t));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::uint8_t>, char32_t));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::uint8_t>, float));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::uint8_t>, double));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::uint8_t>, long double));

    // std::uint16_t
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::uint16_t>, std::int8_t));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::uint16_t>, std::int16_t));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::uint16_t>, std::int32_t));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::uint16_t>, std::int64_t));

    STATIC_REQUIRE(TEST_CONVERSION(phi::Integer<std::uint16_t>, std::uint8_t));
    STATIC_REQUIRE(TEST_CONVERSION(phi::Integer<std::uint16_t>, std::uint16_t));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::uint16_t>, std::uint32_t));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::uint16_t>, std::uint64_t));

    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::uint16_t>, bool));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::uint16_t>, char));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::uint16_t>, wchar_t));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::uint16_t>, char16_t));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::uint16_t>, char32_t));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::uint16_t>, float));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::uint16_t>, double));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::uint16_t>, long double));

    // std::uint32_t
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::uint32_t>, std::int8_t));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::uint32_t>, std::int16_t));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::uint32_t>, std::int32_t));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::uint32_t>, std::int64_t));

    STATIC_REQUIRE(TEST_CONVERSION(phi::Integer<std::uint32_t>, std::uint8_t));
    STATIC_REQUIRE(TEST_CONVERSION(phi::Integer<std::uint32_t>, std::uint16_t));
    STATIC_REQUIRE(TEST_CONVERSION(phi::Integer<std::uint32_t>, std::uint32_t));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::uint32_t>, std::uint64_t));

    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::uint32_t>, bool));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::uint32_t>, char));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::uint32_t>, wchar_t));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::uint32_t>, char16_t));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::uint32_t>, char32_t));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::uint32_t>, float));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::uint32_t>, double));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::uint32_t>, long double));

    // std::uint64_t
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::uint64_t>, std::int8_t));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::uint64_t>, std::int16_t));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::uint64_t>, std::int32_t));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::uint64_t>, std::int64_t));

    STATIC_REQUIRE(TEST_CONVERSION(phi::Integer<std::uint64_t>, std::uint8_t));
    STATIC_REQUIRE(TEST_CONVERSION(phi::Integer<std::uint64_t>, std::uint16_t));
    STATIC_REQUIRE(TEST_CONVERSION(phi::Integer<std::uint64_t>, std::uint32_t));
    STATIC_REQUIRE(TEST_CONVERSION(phi::Integer<std::uint64_t>, std::uint64_t));

    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::uint64_t>, bool));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::uint64_t>, char));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::uint64_t>, wchar_t));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::uint64_t>, char16_t));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::uint64_t>, char32_t));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::uint64_t>, float));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::uint64_t>, double));
    STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::Integer<std::uint64_t>, long double));
}

TEST_CASE("Integer", "[Utility][Types][Integer]")
{
    using int_t = phi::Integer<std::int32_t>;

    SECTION("Type traits")
    {
        // this_type
        STATIC_REQUIRE(
                std::is_same_v<phi::Integer<std::int8_t>::this_type, phi::Integer<std::int8_t>>);
        STATIC_REQUIRE(
                std::is_same_v<phi::Integer<std::int16_t>::this_type, phi::Integer<std::int16_t>>);
        STATIC_REQUIRE(
                std::is_same_v<phi::Integer<std::int32_t>::this_type, phi::Integer<std::int32_t>>);
        STATIC_REQUIRE(
                std::is_same_v<phi::Integer<std::int64_t>::this_type, phi::Integer<std::int64_t>>);

        STATIC_REQUIRE(
                std::is_same_v<phi::Integer<std::uint8_t>::this_type, phi::Integer<std::uint8_t>>);
        STATIC_REQUIRE(std::is_same_v<phi::Integer<std::uint16_t>::this_type,
                                      phi::Integer<std::uint16_t>>);
        STATIC_REQUIRE(std::is_same_v<phi::Integer<std::uint32_t>::this_type,
                                      phi::Integer<std::uint32_t>>);
        STATIC_REQUIRE(std::is_same_v<phi::Integer<std::uint64_t>::this_type,
                                      phi::Integer<std::uint64_t>>);

        // value_type
        STATIC_REQUIRE(std::is_same_v<phi::Integer<std::int8_t>::value_type, std::int8_t>);
        STATIC_REQUIRE(std::is_same_v<phi::Integer<std::int16_t>::value_type, std::int16_t>);
        STATIC_REQUIRE(std::is_same_v<phi::Integer<std::int32_t>::value_type, std::int32_t>);
        STATIC_REQUIRE(std::is_same_v<phi::Integer<std::int64_t>::value_type, std::int64_t>);

        STATIC_REQUIRE(std::is_same_v<phi::Integer<std::uint8_t>::value_type, std::uint8_t>);
        STATIC_REQUIRE(std::is_same_v<phi::Integer<std::uint16_t>::value_type, std::uint16_t>);
        STATIC_REQUIRE(std::is_same_v<phi::Integer<std::uint32_t>::value_type, std::uint32_t>);
        STATIC_REQUIRE(std::is_same_v<phi::Integer<std::uint64_t>::value_type, std::uint64_t>);

        // limits_type
        STATIC_REQUIRE(std::is_same_v<phi::Integer<std::int8_t>::limits_type,
                                      std::numeric_limits<std::int8_t>>);
        STATIC_REQUIRE(std::is_same_v<phi::Integer<std::int16_t>::limits_type,
                                      std::numeric_limits<std::int16_t>>);
        STATIC_REQUIRE(std::is_same_v<phi::Integer<std::int32_t>::limits_type,
                                      std::numeric_limits<std::int32_t>>);
        STATIC_REQUIRE(std::is_same_v<phi::Integer<std::int64_t>::limits_type,
                                      std::numeric_limits<std::int64_t>>);

        STATIC_REQUIRE(std::is_same_v<phi::Integer<std::uint8_t>::limits_type,
                                      std::numeric_limits<std::uint8_t>>);
        STATIC_REQUIRE(std::is_same_v<phi::Integer<std::uint16_t>::limits_type,
                                      std::numeric_limits<std::uint16_t>>);
        STATIC_REQUIRE(std::is_same_v<phi::Integer<std::uint32_t>::limits_type,
                                      std::numeric_limits<std::uint32_t>>);
        STATIC_REQUIRE(std::is_same_v<phi::Integer<std::uint64_t>::limits_type,
                                      std::numeric_limits<std::uint64_t>>);
    }

    SECTION("constructor")
    {
        CONSTEXPR_RUNTIME int_t a(0);
        STATIC_REQUIRE(static_cast<std::int32_t>(a) == 0);
        CONSTEXPR_RUNTIME int_t b(32);
        STATIC_REQUIRE(static_cast<std::int32_t>(b) == 32);
        CONSTEXPR_RUNTIME int_t c(-25);
        STATIC_REQUIRE(static_cast<std::int32_t>(c) == -25);
    }

    SECTION("assignment")
    {
        int_t a(0);
        a = 32;
        CHECK(static_cast<std::int32_t>(a) == 32);
        a = -25;
        CHECK(static_cast<std::int32_t>(a) == -25);
    }

    SECTION("unary")
    {
        CONSTEXPR_RUNTIME int_t a(13);
        STATIC_REQUIRE(static_cast<std::int32_t>(+a) == static_cast<std::int32_t>(a));
        STATIC_REQUIRE(static_cast<std::int32_t>(-a) == -static_cast<std::int32_t>(a));
    }

    SECTION("increment")
    {
        int_t a(0);
        CHECK(static_cast<std::int32_t>(++a) == 1);
        CHECK(static_cast<std::int32_t>(a++) == 1);
        CHECK(static_cast<std::int32_t>(a) == 2);
    }

    SECTION("decrement")
    {
        int_t a(0);
        CHECK(static_cast<std::int32_t>(--a) == -1);
        CHECK(static_cast<std::int32_t>(a--) == -1);
        CHECK(static_cast<std::int32_t>(a) == -2);
    }

    SECTION("addition")
    {
        int_t        wrapper(0);
        std::int32_t normal(0);
        CHECK(static_cast<std::int32_t>(wrapper) == normal);

        wrapper += 5;
        normal += 5;
        CHECK(static_cast<std::int32_t>(wrapper) == normal);

        wrapper += std::int16_t(5);
        normal += std::int16_t(5);
        CHECK(static_cast<std::int32_t>(wrapper) == normal);

        wrapper = wrapper + (-23);
        normal  = normal + (-23);
        CHECK(static_cast<std::int32_t>(wrapper) == normal);

        wrapper = 22 + wrapper;
        normal  = 22 + normal;
        CHECK(static_cast<std::int32_t>(wrapper) == normal);

        wrapper = int_t(-4) + wrapper;
        normal  = (-4) + normal;
        CHECK(static_cast<std::int32_t>(wrapper) == normal);
    }

    SECTION("subtraction")
    {
        int_t        wrapper(0);
        std::int32_t normal(0);
        CHECK(static_cast<std::int32_t>(wrapper) == normal);

        wrapper -= 5;
        normal -= 5;
        CHECK(static_cast<std::int32_t>(wrapper) == normal);

        wrapper -= std::int16_t(5);
        normal -= std::int16_t(5);
        CHECK(static_cast<std::int32_t>(wrapper) == normal);

        wrapper = wrapper - (-23);
        normal  = normal - (-23);
        CHECK(static_cast<std::int32_t>(wrapper) == normal);

        wrapper = 22 - wrapper;
        normal  = 22 - normal;
        CHECK(static_cast<std::int32_t>(wrapper) == normal);

        wrapper = int_t(-4) - wrapper;
        normal  = (-4) - normal;
        CHECK(static_cast<std::int32_t>(wrapper) == normal);
    }

    SECTION("multiplication")
    {
        int_t        wrapper(1);
        std::int32_t normal(1);
        CHECK(static_cast<std::int32_t>(wrapper) == normal);

        wrapper *= 5;
        normal *= 5;
        CHECK(static_cast<std::int32_t>(wrapper) == normal);

        wrapper *= std::int16_t(5);
        normal *= std::int16_t(5);
        CHECK(static_cast<std::int32_t>(wrapper) == normal);

        wrapper = wrapper * (-23);
        normal  = normal * (-23);
        CHECK(static_cast<std::int32_t>(wrapper) == normal);

        wrapper = 22 * wrapper;
        normal  = 22 * normal;
        CHECK(static_cast<std::int32_t>(wrapper) == normal);

        wrapper = int_t(-4) * wrapper;
        normal  = (-4) * normal;
        CHECK(static_cast<std::int32_t>(wrapper) == normal);
    }

    SECTION("division")
    {
        int_t        wrapper(23 * 25);
        std::int32_t normal(23 * 25);
        CHECK(static_cast<std::int32_t>(wrapper) == normal);

        wrapper /= 5;
        normal /= 5;
        CHECK(static_cast<std::int32_t>(wrapper) == normal);

        wrapper /= std::int16_t(5);
        normal /= std::int16_t(5);
        CHECK(static_cast<std::int32_t>(wrapper) == normal);

        wrapper = wrapper / (-23);
        normal  = normal / (-23);
        CHECK(static_cast<std::int32_t>(wrapper) == normal);

        wrapper = 22 / wrapper;
        normal  = 22 / normal;
        CHECK(static_cast<std::int32_t>(wrapper) == normal);

        wrapper = int_t(-4) / wrapper;
        normal  = (-4) / normal;
        CHECK(static_cast<std::int32_t>(wrapper) == normal);
    }

    SECTION("modulo")
    {
        int_t        wrapper(24 * 6);
        std::int32_t normal(24 * 6);
        CHECK(static_cast<std::int32_t>(wrapper) == normal);

        wrapper %= 5;
        normal %= 5;
        CHECK(static_cast<std::int32_t>(wrapper) == normal);

        wrapper %= std::int16_t(5);
        normal %= std::int16_t(5);
        CHECK(static_cast<std::int32_t>(wrapper) == normal);

        wrapper = wrapper % (-23);
        normal  = normal % (-23);
        CHECK(static_cast<std::int32_t>(wrapper) == normal);

        wrapper = 22 % wrapper;
        normal  = 22 % normal;
        CHECK(static_cast<std::int32_t>(wrapper) == normal);

        wrapper = int_t(-4) % wrapper;
        normal  = (-4) % normal;
        CHECK(static_cast<std::int32_t>(wrapper) == normal);
    }

    SECTION("comparison")
    {
        // ==
        STATIC_REQUIRE(bool(int_t(4) == int_t(4)));
        STATIC_REQUIRE(!(int_t(5) == int_t(4)));

        STATIC_REQUIRE(bool(4 == int_t(4)));
        STATIC_REQUIRE(!(5 == int_t(4)));

        STATIC_REQUIRE(bool(int_t(4) == 4));
        STATIC_REQUIRE(!(int_t(5) == 4));

        // !=
        STATIC_REQUIRE(bool(int_t(5) != int_t(4)));
        STATIC_REQUIRE(!(int_t(4) != int_t(4)));

        STATIC_REQUIRE(bool(5 != int_t(4)));
        STATIC_REQUIRE(!(4 != int_t(4)));

        STATIC_REQUIRE(bool(int_t(5) != 4));
        STATIC_REQUIRE(!(int_t(4) != 4));

        // <
        STATIC_REQUIRE(bool(int_t(4) < int_t(5)));
        STATIC_REQUIRE(!(int_t(5) < int_t(4)));
        STATIC_REQUIRE(!(int_t(4) < int_t(4)));

        STATIC_REQUIRE(bool(4 < int_t(5)));
        STATIC_REQUIRE(!(5 < int_t(4)));
        STATIC_REQUIRE(!(4 < int_t(4)));

        STATIC_REQUIRE(bool(int_t(4) < 5));
        STATIC_REQUIRE(!(int_t(5) < 4));
        STATIC_REQUIRE(!(int_t(4) < 4));

        // <=
        STATIC_REQUIRE(bool(int_t(4) <= int_t(5)));
        STATIC_REQUIRE(!(int_t(5) <= int_t(4)));
        STATIC_REQUIRE(bool(int_t(4) <= int_t(4)));

        STATIC_REQUIRE(bool(4 <= int_t(5)));
        STATIC_REQUIRE(!(5 <= int_t(4)));
        STATIC_REQUIRE(bool(4 <= int_t(4)));

        STATIC_REQUIRE(bool(int_t(4) <= 5));
        STATIC_REQUIRE(!(int_t(5) <= 4));
        STATIC_REQUIRE(bool(int_t(4) <= 4));

        // >
        STATIC_REQUIRE(bool(int_t(5) > int_t(4)));
        STATIC_REQUIRE(!(int_t(4) > int_t(5)));
        STATIC_REQUIRE(!(int_t(5) > int_t(5)));

        STATIC_REQUIRE(bool(5 > int_t(4)));
        STATIC_REQUIRE(!(4 > int_t(5)));
        STATIC_REQUIRE(!(5 > int_t(5)));

        STATIC_REQUIRE(bool(int_t(5) > 4));
        STATIC_REQUIRE(!(int_t(4) > 5));
        STATIC_REQUIRE(!(int_t(5) > 5));

        // >=
        STATIC_REQUIRE(bool(int_t(5) >= int_t(4)));
        STATIC_REQUIRE(!(int_t(4) >= int_t(5)));
        STATIC_REQUIRE(bool(int_t(5) >= int_t(5)));

        STATIC_REQUIRE(bool(5 >= int_t(4)));
        STATIC_REQUIRE(!(4 >= int_t(5)));
        STATIC_REQUIRE(bool(5 >= int_t(5)));

        STATIC_REQUIRE(bool(int_t(5) >= 4));
        STATIC_REQUIRE(!(int_t(4) >= 5));
        STATIC_REQUIRE(bool(int_t(5) >= 5));
    }

    SECTION("make_(un)signed")
    {
        int_t                       a = 5;
        phi::Integer<std::uint32_t> b = phi::make_unsigned(a);
        CHECK(static_cast<std::uint32_t>(b) == 5);

        b = 125u;
        a = phi::make_signed(b);
        CHECK(static_cast<std::int32_t>(a) == 125);
    }

    SECTION("i/o")
    {
        std::ostringstream out;
        std::istringstream in("10");

        int_t i(0);
        out << i;
        CHECK(out.str() == "0");

        in >> i;
        CHECK(static_cast<std::int32_t>(i) == 10);
    }

    SECTION("abs")
    {
        CONSTEXPR_RUNTIME std::int32_t i = 123;
        STATIC_REQUIRE(phi::abs(i) == 123u);

        CONSTEXPR_RUNTIME std::int32_t i2 = -123;
        STATIC_REQUIRE(phi::abs(i2) == 123u);

        CONSTEXPR_RUNTIME std::uint32_t unsigned_i = 12u;
        STATIC_REQUIRE(phi::abs(unsigned_i) == 12u);

        CONSTEXPR_RUNTIME phi::Integer<std::int32_t> phi_pos = 123;
        STATIC_REQUIRE(bool(phi::abs(phi_pos) == 123u));

        CONSTEXPR_RUNTIME phi::Integer<std::int32_t> phi_neg = -123;
        STATIC_REQUIRE(bool(phi::abs(phi_neg) == 123u));

        CONSTEXPR_RUNTIME phi::Integer<std::uint32_t> phi_unsigned = 12u;
        STATIC_REQUIRE(bool(phi::abs(phi_unsigned) == 12u));
    }

    SECTION("signed_to_unsigned")
    {
        // From int8_t
        STATIC_REQUIRE(!std::is_convertible_v<phi::Integer<int8_t>, phi::Integer<uint8_t>>);
        STATIC_REQUIRE(!std::is_convertible_v<phi::Integer<int8_t>, phi::Integer<uint16_t>>);
        STATIC_REQUIRE(!std::is_convertible_v<phi::Integer<int8_t>, phi::Integer<uint32_t>>);
        STATIC_REQUIRE(!std::is_convertible_v<phi::Integer<int8_t>, phi::Integer<uint64_t>>);

        // From int16_t
        STATIC_REQUIRE(!std::is_convertible_v<phi::Integer<int16_t>, phi::Integer<uint8_t>>);
        STATIC_REQUIRE(!std::is_convertible_v<phi::Integer<int16_t>, phi::Integer<uint16_t>>);
        STATIC_REQUIRE(!std::is_convertible_v<phi::Integer<int16_t>, phi::Integer<uint32_t>>);
        STATIC_REQUIRE(!std::is_convertible_v<phi::Integer<int16_t>, phi::Integer<uint64_t>>);

        // From int32_t
        STATIC_REQUIRE(!std::is_convertible_v<phi::Integer<int32_t>, phi::Integer<uint8_t>>);
        STATIC_REQUIRE(!std::is_convertible_v<phi::Integer<int32_t>, phi::Integer<uint16_t>>);
        STATIC_REQUIRE(!std::is_convertible_v<phi::Integer<int32_t>, phi::Integer<uint32_t>>);
        STATIC_REQUIRE(!std::is_convertible_v<phi::Integer<int32_t>, phi::Integer<uint64_t>>);

        // From int64_t
        STATIC_REQUIRE(!std::is_convertible_v<phi::Integer<int64_t>, phi::Integer<uint8_t>>);
        STATIC_REQUIRE(!std::is_convertible_v<phi::Integer<int64_t>, phi::Integer<uint16_t>>);
        STATIC_REQUIRE(!std::is_convertible_v<phi::Integer<int64_t>, phi::Integer<uint32_t>>);
        STATIC_REQUIRE(!std::is_convertible_v<phi::Integer<int64_t>, phi::Integer<uint64_t>>);
    }

    SECTION("unsigned_to_signed")
    {
        // From uint8_t
        STATIC_REQUIRE(!std::is_convertible_v<phi::Integer<uint8_t>, phi::Integer<int8_t>>);
        STATIC_REQUIRE(std::is_convertible_v<phi::Integer<uint8_t>, phi::Integer<int16_t>>);
        STATIC_REQUIRE(std::is_convertible_v<phi::Integer<uint8_t>, phi::Integer<int32_t>>);
        STATIC_REQUIRE(std::is_convertible_v<phi::Integer<uint8_t>, phi::Integer<int64_t>>);

        // From uint16_t
        STATIC_REQUIRE(!std::is_convertible_v<phi::Integer<uint16_t>, phi::Integer<int8_t>>);
        STATIC_REQUIRE(!std::is_convertible_v<phi::Integer<uint16_t>, phi::Integer<int16_t>>);
        STATIC_REQUIRE(std::is_convertible_v<phi::Integer<uint16_t>, phi::Integer<int32_t>>);
        STATIC_REQUIRE(std::is_convertible_v<phi::Integer<uint16_t>, phi::Integer<int64_t>>);

        // From uint32_t
        STATIC_REQUIRE(!std::is_convertible_v<phi::Integer<uint32_t>, phi::Integer<int8_t>>);
        STATIC_REQUIRE(!std::is_convertible_v<phi::Integer<uint32_t>, phi::Integer<int16_t>>);
        STATIC_REQUIRE(!std::is_convertible_v<phi::Integer<uint32_t>, phi::Integer<int32_t>>);
        STATIC_REQUIRE(std::is_convertible_v<phi::Integer<uint32_t>, phi::Integer<int64_t>>);

        // From uint64_t
        STATIC_REQUIRE(!std::is_convertible_v<phi::Integer<uint64_t>, phi::Integer<int8_t>>);
        STATIC_REQUIRE(!std::is_convertible_v<phi::Integer<uint64_t>, phi::Integer<int16_t>>);
        STATIC_REQUIRE(!std::is_convertible_v<phi::Integer<uint64_t>, phi::Integer<int32_t>>);
        STATIC_REQUIRE(!std::is_convertible_v<phi::Integer<uint64_t>, phi::Integer<int64_t>>);
    }

    SECTION("signed_to_signed")
    {
        // From int8_t
        STATIC_REQUIRE(std::is_convertible_v<phi::Integer<int8_t>, phi::Integer<int8_t>>);
        STATIC_REQUIRE(std::is_convertible_v<phi::Integer<int8_t>, phi::Integer<int16_t>>);
        STATIC_REQUIRE(std::is_convertible_v<phi::Integer<int8_t>, phi::Integer<int32_t>>);
        STATIC_REQUIRE(std::is_convertible_v<phi::Integer<int8_t>, phi::Integer<int64_t>>);

        // From int16_t
        STATIC_REQUIRE(!std::is_convertible_v<phi::Integer<int16_t>, phi::Integer<int8_t>>);
        STATIC_REQUIRE(std::is_convertible_v<phi::Integer<int16_t>, phi::Integer<int16_t>>);
        STATIC_REQUIRE(std::is_convertible_v<phi::Integer<int16_t>, phi::Integer<int32_t>>);
        STATIC_REQUIRE(std::is_convertible_v<phi::Integer<int16_t>, phi::Integer<int64_t>>);

        // From int32_t
        STATIC_REQUIRE(!std::is_convertible_v<phi::Integer<int32_t>, phi::Integer<int8_t>>);
        STATIC_REQUIRE(!std::is_convertible_v<phi::Integer<int32_t>, phi::Integer<int16_t>>);
        STATIC_REQUIRE(std::is_convertible_v<phi::Integer<int32_t>, phi::Integer<int32_t>>);
        STATIC_REQUIRE(std::is_convertible_v<phi::Integer<int32_t>, phi::Integer<int64_t>>);

        // From int64_t
        STATIC_REQUIRE(!std::is_convertible_v<phi::Integer<int64_t>, phi::Integer<int8_t>>);
        STATIC_REQUIRE(!std::is_convertible_v<phi::Integer<int64_t>, phi::Integer<int16_t>>);
        STATIC_REQUIRE(!std::is_convertible_v<phi::Integer<int64_t>, phi::Integer<int32_t>>);
        STATIC_REQUIRE(std::is_convertible_v<phi::Integer<int64_t>, phi::Integer<int64_t>>);
    }

    SECTION("unsigned_to_unsigned")
    {
        // From uint8_t
        STATIC_REQUIRE(std::is_convertible_v<phi::Integer<uint8_t>, phi::Integer<uint8_t>>);
        STATIC_REQUIRE(std::is_convertible_v<phi::Integer<uint8_t>, phi::Integer<uint16_t>>);
        STATIC_REQUIRE(std::is_convertible_v<phi::Integer<uint8_t>, phi::Integer<uint32_t>>);
        STATIC_REQUIRE(std::is_convertible_v<phi::Integer<uint8_t>, phi::Integer<uint64_t>>);

        // From uint16_t
        STATIC_REQUIRE(!std::is_convertible_v<phi::Integer<uint16_t>, phi::Integer<uint8_t>>);
        STATIC_REQUIRE(std::is_convertible_v<phi::Integer<uint16_t>, phi::Integer<uint16_t>>);
        STATIC_REQUIRE(std::is_convertible_v<phi::Integer<uint16_t>, phi::Integer<uint32_t>>);
        STATIC_REQUIRE(std::is_convertible_v<phi::Integer<uint16_t>, phi::Integer<uint64_t>>);

        // From uint32_t
        STATIC_REQUIRE(!std::is_convertible_v<phi::Integer<uint32_t>, phi::Integer<uint8_t>>);
        STATIC_REQUIRE(!std::is_convertible_v<phi::Integer<uint32_t>, phi::Integer<uint16_t>>);
        STATIC_REQUIRE(std::is_convertible_v<phi::Integer<uint32_t>, phi::Integer<uint32_t>>);
        STATIC_REQUIRE(std::is_convertible_v<phi::Integer<uint32_t>, phi::Integer<uint64_t>>);

        // From uint64_t
        STATIC_REQUIRE(!std::is_convertible_v<phi::Integer<uint64_t>, phi::Integer<uint8_t>>);
        STATIC_REQUIRE(!std::is_convertible_v<phi::Integer<uint64_t>, phi::Integer<uint16_t>>);
        STATIC_REQUIRE(!std::is_convertible_v<phi::Integer<uint64_t>, phi::Integer<uint32_t>>);
        STATIC_REQUIRE(std::is_convertible_v<phi::Integer<uint64_t>, phi::Integer<uint64_t>>);
    }

    SECTION("std::hash")
    {
        std::size_t zero_hash = std::hash<phi::Integer<int>>{}(0);
        std::size_t one_hash  = std::hash<phi::Integer<int>>{}(1);

        CHECK(zero_hash != one_hash);
        CHECK(zero_hash == std::hash<int>{}(0));
        CHECK(one_hash == std::hash<int>{}(1));
    }
}

CPP_GCC_SUPPRESS_WARNING_POP
