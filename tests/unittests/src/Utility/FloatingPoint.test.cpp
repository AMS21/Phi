// This file is heavily inspired by Jonathan Müllers <jonathanmueller.dev@gmail.com> type_safe library https://github.com/foonathan/type_safe
// licensed under the MIT license https://github.com/foonathan/type_safe/blob/master/LICENSE
// Original file at https://github.com/foonathan/type_safe/blob/master/test/floating_point.cpp
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
#include <Phi/Utility/FloatingPoint.hpp>
#include <catch2/catch.hpp>
#include <cpp/Warning.hpp>
#include <cfloat>
#include <sstream>
#include <type_traits>

CPP_CLANG_SUPPRESS_WARNING_PUSH
CPP_CLANG_SUPPRESS_WARNING("-Wfloat-equal")

CPP_GCC_SUPPRESS_WARNING_PUSH
CPP_GCC_SUPPRESS_WARNING("-Wfloat-equal")
CPP_GCC_SUPPRESS_WARNING("-Wuseless-cast")

TEST_CASE("FloatingPoint layout", "[Utility][Typs][FlooatingType]")
{
    STATIC_REQUIRE(sizeof(float) == sizeof(phi::FloatingPoint<float>));
    STATIC_REQUIRE(std::is_trivially_copyable_v<phi::FloatingPoint<float>>);
    STATIC_REQUIRE(std::is_standard_layout_v<phi::FloatingPoint<float>>);
    STATIC_REQUIRE_FALSE(std::is_default_constructible_v<phi::FloatingPoint<float>>);

    // conversion checks
    STATIC_REQUIRE(std::is_constructible_v<phi::FloatingPoint<float>, float>);
    STATIC_REQUIRE_FALSE(std::is_constructible_v<phi::FloatingPoint<float>, double>);
    STATIC_REQUIRE_FALSE(std::is_constructible_v<phi::FloatingPoint<float>, long double>);
    STATIC_REQUIRE(std::is_constructible_v<phi::FloatingPoint<double>, float>);
    STATIC_REQUIRE(std::is_constructible_v<phi::FloatingPoint<double>, double>);
#if (DBL_DIG < LDBL_DIG)
    STATIC_REQUIRE_FALSE(std::is_constructible_v<phi::FloatingPoint<double>, long double>);
#else
    STATIC_REQUIRE(std::is_constructible_v<phi::FloatingPoint<double>, long double>);
#endif
    STATIC_REQUIRE(std::is_constructible_v<phi::FloatingPoint<long double>, float>);
    STATIC_REQUIRE(std::is_constructible_v<phi::FloatingPoint<long double>, double>);
    STATIC_REQUIRE(std::is_constructible_v<phi::FloatingPoint<long double>, long double>);

    STATIC_REQUIRE(std::is_constructible_v<phi::FloatingPoint<float>, phi::FloatingPoint<float>>);
    STATIC_REQUIRE_FALSE(
            std::is_constructible_v<phi::FloatingPoint<float>, phi::FloatingPoint<double>>);
    STATIC_REQUIRE_FALSE(
            std::is_constructible_v<phi::FloatingPoint<float>, phi::FloatingPoint<long double>>);
    STATIC_REQUIRE(std::is_constructible_v<phi::FloatingPoint<double>, phi::FloatingPoint<float>>);
    STATIC_REQUIRE(std::is_constructible_v<phi::FloatingPoint<double>, phi::FloatingPoint<double>>);
#if (DBL_DIG < LDBL_DIG)
    STATIC_REQUIRE_FALSE(
            std::is_constructible_v<phi::FloatingPoint<double>, phi::FloatingPoint<long double>>);
#else
    STATIC_REQUIRE(
            std::is_constructible_v<phi::FloatingPoint<double>, phi::FloatingPoint<double long>>);
#endif
    STATIC_REQUIRE(
            std::is_constructible_v<phi::FloatingPoint<long double>, phi::FloatingPoint<float>>);
    STATIC_REQUIRE(
            std::is_constructible_v<phi::FloatingPoint<long double>, phi::FloatingPoint<double>>);
    STATIC_REQUIRE(std::is_constructible_v<phi::FloatingPoint<long double>,
                                           phi::FloatingPoint<long double>>);

    // assignment
    STATIC_REQUIRE(std::is_assignable_v<phi::FloatingPoint<float>, float>);
    STATIC_REQUIRE_FALSE(std::is_assignable_v<phi::FloatingPoint<float>, double>);
    STATIC_REQUIRE_FALSE(std::is_assignable_v<phi::FloatingPoint<float>, long double>);
    STATIC_REQUIRE(std::is_assignable_v<phi::FloatingPoint<double>, float>);
    STATIC_REQUIRE(std::is_assignable_v<phi::FloatingPoint<double>, double>);
#if (DBL_DIG < LDBL_DIG)
    STATIC_REQUIRE_FALSE(std::is_assignable_v<phi::FloatingPoint<double>, long double>);
#else
    STATIC_REQUIRE(std::is_assignable_v<phi::FloatingPoint<double>, long double>);
#endif
    STATIC_REQUIRE(std::is_assignable_v<phi::FloatingPoint<long double>, float>);
    STATIC_REQUIRE(std::is_assignable_v<phi::FloatingPoint<long double>, double>);
    STATIC_REQUIRE(std::is_assignable_v<phi::FloatingPoint<long double>, long double>);

    STATIC_REQUIRE(std::is_assignable_v<phi::FloatingPoint<float>, phi::FloatingPoint<float>>);
    STATIC_REQUIRE_FALSE(
            std::is_assignable_v<phi::FloatingPoint<float>, phi::FloatingPoint<double>>);
    STATIC_REQUIRE_FALSE(
            std::is_assignable_v<phi::FloatingPoint<float>, phi::FloatingPoint<long double>>);
    STATIC_REQUIRE(std::is_assignable_v<phi::FloatingPoint<double>, phi::FloatingPoint<float>>);
    STATIC_REQUIRE(std::is_assignable_v<phi::FloatingPoint<double>, phi::FloatingPoint<double>>);
#if (DBL_DIG < LDBL_DIG)
    STATIC_REQUIRE_FALSE(
            std::is_assignable_v<phi::FloatingPoint<double>, phi::FloatingPoint<long double>>);
#else
    STATIC_REQUIRE(
            std::is_assignable_v<phi::FloatingPoint<double>, phi::FloatingPoint<long double>>);
#endif
    STATIC_REQUIRE(
            std::is_assignable_v<phi::FloatingPoint<long double>, phi::FloatingPoint<float>>);
    STATIC_REQUIRE(
            std::is_assignable_v<phi::FloatingPoint<long double>, phi::FloatingPoint<double>>);
    STATIC_REQUIRE(
            std::is_assignable_v<phi::FloatingPoint<long double>, phi::FloatingPoint<long double>>);
}

TEST_CASE("phi::FloatingPoint", "[Utility][Typs][FloatingPoint]")
{
    using FloatT = phi::FloatingPoint<double>;

    SECTION("constructor")
    {
        CONSTEXPR_RUNTIME FloatT a(0.0);
        STATIC_REQUIRE(static_cast<double>(a) == 0.0);

        CONSTEXPR_RUNTIME FloatT b(3.14);
        STATIC_REQUIRE(static_cast<double>(b) == 3.14);

        CONSTEXPR_RUNTIME FloatT c(-42.5);
        STATIC_REQUIRE(static_cast<double>(c) == -42.5);
    }

    SECTION("assignment")
    {
        FloatT a(0.0);
        a = 3.14;
        CHECK(static_cast<double>(a) == 3.14);
        a = -42.5;
        CHECK(static_cast<double>(a) == -42.5);
    }

    SECTION("unary")
    {
        CONSTEXPR_RUNTIME FloatT a(13.255);
        STATIC_REQUIRE(static_cast<double>(+a) == static_cast<double>(a));
        STATIC_REQUIRE(static_cast<double>(-a) == -static_cast<double>(a));
    }

    SECTION("addition")
    {
        FloatT wrapper(0.0);
        double normal(0.0);
        CHECK(static_cast<double>(wrapper) == normal);

        wrapper += 4.5;
        normal += 4.5;
        CHECK(static_cast<double>(wrapper) == normal);

        wrapper = wrapper + (-2.3);
        normal  = normal + (-2.3);
        CHECK(static_cast<double>(wrapper) == normal);

        wrapper = 1.1 + wrapper;
        normal  = 1.1 + normal;
        CHECK(static_cast<double>(wrapper) == normal);

        wrapper = FloatT(-11.0) + wrapper;
        normal  = -11.0 + normal;
        CHECK(static_cast<double>(wrapper) == normal);
    }

    SECTION("subtraction")
    {
        FloatT wrapper(0.0);
        double normal(0.0);
        CHECK(static_cast<double>(wrapper) == normal);

        wrapper -= 4.5;
        normal -= 4.5;
        CHECK(static_cast<double>(wrapper) == normal);

        wrapper = wrapper - (-2.3);
        normal  = normal - (-2.3);
        CHECK(static_cast<double>(wrapper) == normal);

        wrapper = 1.1 - wrapper;
        normal  = 1.1 - normal;
        CHECK(static_cast<double>(wrapper) == normal);

        wrapper = FloatT(-11.0) - wrapper;
        normal  = -11.0 - normal;
        CHECK(static_cast<double>(wrapper) == normal);
    }

    SECTION("multiplication")
    {
        FloatT wrapper(1.);
        double normal(1.);
        CHECK(static_cast<double>(wrapper) == normal);

        wrapper *= 4.5;
        normal *= 4.5;
        CHECK(static_cast<double>(wrapper) == normal);

        wrapper = wrapper * (-2.3);
        normal  = normal * (-2.3);
        CHECK(static_cast<double>(wrapper) == normal);

        wrapper = 1.1 * wrapper;
        normal  = 1.1 * normal;
        CHECK(static_cast<double>(wrapper) == normal);

        wrapper = FloatT(-11.0) * wrapper;
        normal  = -11.0 * normal;
        CHECK(static_cast<double>(wrapper) == normal);
    }

    SECTION("division")
    {
        FloatT wrapper(10.);
        double normal(10.);
        CHECK(static_cast<double>(wrapper) == normal);

        wrapper /= 4.5;
        normal /= 4.5;
        CHECK(static_cast<double>(wrapper) == normal);

        wrapper = wrapper / (-2.3);
        normal  = normal / (-2.3);
        CHECK(static_cast<double>(wrapper) == normal);

        wrapper = 1.1 / wrapper;
        normal  = 1.1 / normal;
        CHECK(static_cast<double>(wrapper) == normal);

        wrapper = FloatT(-11.0) / wrapper;
        normal  = -11.0 / normal;
        CHECK(static_cast<double>(wrapper) == normal);
    }

    SECTION("comparison")
    {
        // <
        STATIC_REQUIRE(bool(FloatT(4.0) < FloatT(5.0)));
        STATIC_REQUIRE_FALSE(bool(FloatT(5.0) < FloatT(4.0)));
        STATIC_REQUIRE_FALSE(bool(FloatT(4.0) < FloatT(4.0)));

        STATIC_REQUIRE(bool(4.0 < FloatT(5.0)));
        STATIC_REQUIRE_FALSE(bool(5.0 < FloatT(4.0)));
        STATIC_REQUIRE_FALSE(bool(4.0 < FloatT(4.0)));

        STATIC_REQUIRE(bool(FloatT(4.0) < 5.0));
        STATIC_REQUIRE_FALSE(bool(FloatT(5.0) < 4.0));
        STATIC_REQUIRE_FALSE(bool(FloatT(4.0) < 4.0));

        // <=
        STATIC_REQUIRE(bool(FloatT(4.0) <= FloatT(5.0)));
        STATIC_REQUIRE_FALSE(bool(FloatT(5.0) <= FloatT(4.0)));
        STATIC_REQUIRE(bool(FloatT(4.0) <= FloatT(4.0)));

        STATIC_REQUIRE(bool(4.0 <= FloatT(5.0)));
        STATIC_REQUIRE_FALSE(bool(5.0 <= FloatT(4.0)));
        STATIC_REQUIRE(bool(4.0 <= FloatT(4.0)));

        STATIC_REQUIRE(bool(FloatT(4.0) <= 5.0));
        STATIC_REQUIRE_FALSE(bool(FloatT(5.0) <= 4.0));
        STATIC_REQUIRE(bool(FloatT(4.0) <= 4.0));

        // >
        STATIC_REQUIRE(bool(FloatT(5.0) > FloatT(4.0)));
        STATIC_REQUIRE_FALSE(bool(FloatT(4.0) > FloatT(5.0)));
        STATIC_REQUIRE_FALSE(bool(FloatT(5.0) > FloatT(5.0)));

        STATIC_REQUIRE(bool(5.0 > FloatT(4.0)));
        STATIC_REQUIRE_FALSE(bool(4.0 > FloatT(5.0)));
        STATIC_REQUIRE_FALSE(bool(5.0 > FloatT(5.0)));

        STATIC_REQUIRE(bool(FloatT(5.0) > 4.0));
        STATIC_REQUIRE_FALSE(bool(FloatT(4.0) > 5.0));
        STATIC_REQUIRE_FALSE(bool(FloatT(5.0) > 5.0));

        // >=
        STATIC_REQUIRE(bool(FloatT(5.0) >= FloatT(4.0)));
        STATIC_REQUIRE_FALSE(bool(FloatT(4.0) >= FloatT(5.0)));
        STATIC_REQUIRE(bool(FloatT(5.0) >= FloatT(5.0)));

        STATIC_REQUIRE(bool(5.0 >= FloatT(4.0)));
        STATIC_REQUIRE_FALSE(bool(4.0 >= FloatT(5.0)));
        STATIC_REQUIRE(bool(5.0 >= FloatT(5.0)));

        STATIC_REQUIRE(bool(FloatT(5.0) >= 4.0));
        STATIC_REQUIRE_FALSE(bool(FloatT(4.0) >= 5.0));
        STATIC_REQUIRE(bool(FloatT(5.0) >= 5.0));
    }

    SECTION("i/o")
    {
        std::ostringstream out;
        std::istringstream in("1.0");

        FloatT f(0.0);
        out << f;
        CHECK(out.str() == "0");

        in >> f;
        CHECK(static_cast<double>(f) == 1.0);
    }

    SECTION("get")
    {
        CONSTEXPR_RUNTIME FloatT f(0.0);
        STATIC_REQUIRE(f.get() == 0.0);
    }
}

CPP_GCC_SUPPRESS_WARNING_POP
CPP_CLANG_SUPPRESS_WARNING_POP
