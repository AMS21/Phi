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
#include <catch2/catch.hpp>

#include "ConstexprHelper.hpp"
#include <Phi/Utility/Integer.hpp>
#include <catch2/catch.hpp>
#include <cpp/Warning.hpp>
#include <cstdint>
#include <sstream>

CPP_GCC_SUPPRESS_WARNING_PUSH
CPP_GCC_SUPPRESS_WARNING("-Wuseless-cast")

TEST_CASE("Integer layout", "[Utility][Types][Integer]")
{
    STATIC_REQUIRE(sizeof(phi::Integer<std::int32_t>) == sizeof(std::int32_t));

    STATIC_REQUIRE(std::is_standard_layout_v<phi::Integer<std::int32_t>>);
    STATIC_REQUIRE(std::is_trivially_copyable_v<phi::Integer<std::int32_t>>);
    STATIC_REQUIRE_FALSE(std::is_default_constructible_v<phi::Integer<std::int32_t>>);
}

TEST_CASE("Integer conversion checks", "[Utility][Types][Integer]")
{
    STATIC_REQUIRE(std::is_constructible_v<phi::Integer<std::int16_t>, std::int16_t>);
    STATIC_REQUIRE_FALSE(std::is_constructible_v<phi::Integer<std::int16_t>, std::int32_t>);
    STATIC_REQUIRE_FALSE(std::is_constructible_v<phi::Integer<std::int16_t>, std::uint16_t>);
    STATIC_REQUIRE_FALSE(std::is_constructible_v<phi::Integer<std::uint16_t>, std::int16_t>);

    STATIC_REQUIRE(std::is_assignable_v<phi::Integer<std::int16_t>, std::int16_t>);
    STATIC_REQUIRE_FALSE(std::is_assignable_v<phi::Integer<std::int16_t>, std::int32_t>);
    STATIC_REQUIRE_FALSE(std::is_assignable_v<phi::Integer<std::int16_t>, std::uint16_t>);
    STATIC_REQUIRE_FALSE(std::is_assignable_v<phi::Integer<std::uint16_t>, std::int16_t>);

    STATIC_REQUIRE(std::is_constructible_v<phi::Integer<std::int32_t>, std::int32_t>);
    STATIC_REQUIRE(std::is_constructible_v<phi::Integer<std::int32_t>, std::int16_t>);
    STATIC_REQUIRE_FALSE(std::is_constructible_v<phi::Integer<std::int32_t>, std::int64_t>);
    STATIC_REQUIRE_FALSE(std::is_constructible_v<phi::Integer<std::int32_t>, std::uint32_t>);
    STATIC_REQUIRE_FALSE(std::is_constructible_v<phi::Integer<std::uint32_t>, std::int32_t>);

    STATIC_REQUIRE(std::is_assignable_v<phi::Integer<std::int32_t>, std::int32_t>);
    STATIC_REQUIRE(std::is_assignable_v<phi::Integer<std::int32_t>, std::int16_t>);
    STATIC_REQUIRE_FALSE(std::is_assignable_v<phi::Integer<std::int32_t>, std::int64_t>);
    STATIC_REQUIRE_FALSE(std::is_assignable_v<phi::Integer<std::int32_t>, std::uint32_t>);
    STATIC_REQUIRE_FALSE(std::is_assignable_v<phi::Integer<std::uint32_t>, std::int32_t>);
}

TEST_CASE("Integer", "[Utility][Types][Integer]")
{
    using int_t = phi::Integer<std::int32_t>;

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
        std::int32_t                i  = 123;
        phi::Integer<std::uint32_t> ia = phi::abs(i);
        CHECK(static_cast<std::uint32_t>(ia) == 123u);

        i  = -123;
        ia = phi::abs(i);
        CHECK(static_cast<std::uint32_t>(ia) == 123u);
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
}

CPP_GCC_SUPPRESS_WARNING_POP
