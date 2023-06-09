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

#include <phi/test/test_macros.hpp>

#include "constexpr_helper.hpp"
#include <phi/algorithm/swap.hpp>
#include <phi/compiler_support/warning.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/type_traits/is_default_constructible.hpp>
#include <phi/type_traits/is_nothrow_assignable.hpp>
#include <phi/type_traits/is_nothrow_constructible.hpp>
#include <phi/type_traits/is_standard_layout.hpp>
#include <phi/type_traits/is_trivially_copyable.hpp>
#include <cfloat>
#include <cmath>
#include <functional>
#include <sstream>
#include <string>

#define TEST_CONVERSION(lhs, rhs)                                                                  \
    (phi::is_nothrow_constructible<lhs, rhs>::value && phi::is_nothrow_assignable<lhs, rhs>::value)

PHI_CLANG_SUPPRESS_WARNING("-Wfloat-equal")

PHI_GCC_SUPPRESS_WARNING("-Wfloat-equal")
PHI_GCC_SUPPRESS_WARNING("-Wuseless-cast")
PHI_GCC_SUPPRESS_WARNING("-Wdouble-promotion")

TEST_CASE("floating_point")
{
    SECTION("floating_point layout", "[Utility][Typs][FloatingType]")
    {
        STATIC_REQUIRE(sizeof(float) == sizeof(phi::floating_point<float>));
        STATIC_REQUIRE(sizeof(double) == sizeof(phi::floating_point<double>));
        STATIC_REQUIRE(sizeof(long double) == sizeof(phi::floating_point<long double>));
#if PHI_HAS_WORKING_IS_TRIVIALLY_COPYABLE()
        STATIC_REQUIRE(phi::is_trivially_copyable<phi::floating_point<float>>::value);
#endif
#if PHI_HAS_WORKING_IS_STANDARD_LAYOUT()
        STATIC_REQUIRE(phi::is_standard_layout<phi::floating_point<float>>::value);
#endif
#if PHI_HAS_WORKING_IS_DEFAULT_CONSTRUCTIBLE()
        STATIC_REQUIRE_FALSE(phi::is_default_constructible<phi::floating_point<float>>::value);
#endif

        // conversion checks
        STATIC_REQUIRE(TEST_CONVERSION(phi::floating_point<float>, float));
        STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::floating_point<float>, double));
        STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::floating_point<float>, long double));
        STATIC_REQUIRE(TEST_CONVERSION(phi::floating_point<double>, float));
        STATIC_REQUIRE(TEST_CONVERSION(phi::floating_point<double>, double));
#if (DBL_DIG < LDBL_DIG)
        STATIC_REQUIRE_FALSE(TEST_CONVERSION(phi::floating_point<double>, long double));
#else
        STATIC_REQUIRE(TEST_CONVERSION(phi::floating_point<double>, long double));
#endif
        STATIC_REQUIRE(TEST_CONVERSION(phi::floating_point<long double>, float));
        STATIC_REQUIRE(TEST_CONVERSION(phi::floating_point<long double>, double));
        STATIC_REQUIRE(TEST_CONVERSION(phi::floating_point<long double>, long double));

        STATIC_REQUIRE(TEST_CONVERSION(phi::floating_point<float>, phi::floating_point<float>));
        STATIC_REQUIRE_FALSE(
                TEST_CONVERSION(phi::floating_point<float>, phi::floating_point<double>));
        STATIC_REQUIRE_FALSE(
                TEST_CONVERSION(phi::floating_point<float>, phi::floating_point<long double>));
        STATIC_REQUIRE(TEST_CONVERSION(phi::floating_point<double>, phi::floating_point<float>));
        STATIC_REQUIRE(TEST_CONVERSION(phi::floating_point<double>, phi::floating_point<double>));
#if (DBL_DIG < LDBL_DIG)
        STATIC_REQUIRE_FALSE(
                TEST_CONVERSION(phi::floating_point<double>, phi::floating_point<long double>));
#else
        STATIC_REQUIRE(
                TEST_CONVERSION(phi::floating_point<double>, phi::floating_point<double long>));
#endif
        STATIC_REQUIRE(
                TEST_CONVERSION(phi::floating_point<long double>, phi::floating_point<float>));
        STATIC_REQUIRE(
                TEST_CONVERSION(phi::floating_point<long double>, phi::floating_point<double>));
        STATIC_REQUIRE(TEST_CONVERSION(phi::floating_point<long double>,
                                       phi::floating_point<long double>));

        STATIC_REQUIRE(phi::is_nothrow_constructible<float, phi::floating_point<float>>::value);
        STATIC_REQUIRE_FALSE(
                phi::is_nothrow_constructible<float, phi::floating_point<double>>::value);
        STATIC_REQUIRE_FALSE(
                phi::is_nothrow_constructible<float, phi::floating_point<long double>>::value);
        STATIC_REQUIRE_FALSE(
                phi::is_nothrow_constructible<double, phi::floating_point<float>>::value);
        STATIC_REQUIRE(phi::is_nothrow_constructible<double, phi::floating_point<double>>::value);
        STATIC_REQUIRE_FALSE(
                phi::is_nothrow_constructible<double, phi::floating_point<long double>>::value);
        STATIC_REQUIRE_FALSE(
                phi::is_nothrow_constructible<long double, phi::floating_point<float>>::value);
        STATIC_REQUIRE_FALSE(
                phi::is_nothrow_constructible<long double, phi::floating_point<double>>::value);
        STATIC_REQUIRE(phi::is_nothrow_constructible<long double,
                                                     phi::floating_point<long double>>::value);

        STATIC_REQUIRE_FALSE(phi::is_assignable<float, phi::floating_point<float>>::value);
        STATIC_REQUIRE_FALSE(phi::is_assignable<float, phi::floating_point<double>>::value);
        STATIC_REQUIRE_FALSE(phi::is_assignable<float, phi::floating_point<long double>>::value);
        STATIC_REQUIRE_FALSE(phi::is_assignable<double, phi::floating_point<float>>::value);
        STATIC_REQUIRE_FALSE(phi::is_assignable<double, phi::floating_point<double>>::value);
        STATIC_REQUIRE_FALSE(phi::is_assignable<double, phi::floating_point<long double>>::value);
        STATIC_REQUIRE_FALSE(phi::is_assignable<long double, phi::floating_point<float>>::value);
        STATIC_REQUIRE_FALSE(phi::is_assignable<long double, phi::floating_point<double>>::value);
        STATIC_REQUIRE_FALSE(
                phi::is_assignable<long double, phi::floating_point<long double>>::value);
    }

    SECTION("phi::floating_point", "[Utility][Types][floating_point]")
    {
        using FloatT = phi::floating_point<double>;

        SECTION("constructor")
        {
            constexpr FloatT test1(0.0);
            STATIC_REQUIRE(static_cast<double>(test1) == 0.0);

            constexpr FloatT test2(3.14);
            STATIC_REQUIRE(static_cast<double>(test2) == 3.14);

            constexpr FloatT test3(-42.5);
            STATIC_REQUIRE(static_cast<double>(test3) == -42.5);
        }

        SECTION("assignment")
        {
            FloatT test(0.0);
            test = 3.14;
            CHECK(static_cast<double>(test) == 3.14);
            test = -42.5;
            CHECK(static_cast<double>(test) == -42.5);
        }

        SECTION("unary")
        {
            constexpr FloatT test(13.255);
            STATIC_REQUIRE(static_cast<double>(+test) == static_cast<double>(test));
            STATIC_REQUIRE(static_cast<double>(-test) == -static_cast<double>(test));
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
            FloatT wrapper(1.0);
            double normal(1.0);
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
            FloatT wrapper(10.0);
            double normal(10.0);
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

        SECTION("Module")
        {
            FloatT wrapper(24.0 * 6.0);
            double normal(24.0 * 6.0);
            CHECK(wrapper.unsafe() == normal);

            wrapper %= 5.0;
            normal = std::fmod(normal, 5.0);
            CHECK(wrapper.unsafe() == normal);

            wrapper %= float(5.0);
            normal = std::fmod(normal, float(5.0));
            CHECK(wrapper.unsafe() == normal);

            wrapper = wrapper % (-23.0);
            normal  = std::fmod(normal, (-23.0));
            CHECK(wrapper.unsafe() == normal);

            wrapper = 22.0 % wrapper;
            normal  = std::fmod(22.0, normal);
            CHECK(wrapper.unsafe() == normal);

            wrapper = FloatT(-4.0) % wrapper;
            normal  = std::fmod(-4.0, normal);
            CHECK(wrapper.unsafe() == normal);
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
            std::ostringstream out_stream;
            std::istringstream in_stream("1.0");

            FloatT float_value(0.0);
            out_stream << float_value;
            CHECK(out_stream.str() == "0");

            in_stream >> float_value;
            CHECK(static_cast<double>(float_value) == 1.0);
        }

        SECTION("unsafe")
        {
            constexpr FloatT test(0.0);
            STATIC_REQUIRE(test.unsafe() == 0.0);
        }

        SECTION("std::hash")
        {
            phi::size_t zero_hash = std::hash<phi::floating_point<float>>{}(0.0f);
            phi::size_t one_hash  = std::hash<phi::floating_point<float>>{}(1.0f);

            CHECK(zero_hash != one_hash);
            CHECK(zero_hash == std::hash<float>{}(0.0f));
            CHECK(one_hash == std::hash<float>{}(1.0f));
        }
    }
}

TEST_CASE("core.floating_point.constructor(const floating_point&)")
{
    {
        phi::floating_point<float> value{0.0f};
        phi::floating_point<float> other{value};

        CHECK(value.unsafe() == other.unsafe());
    }
    {
        phi::floating_point<float>  value{0.0f};
        phi::floating_point<double> other{value};

        CHECK(value.unsafe() == other.unsafe());
    }
    {
        phi::floating_point<double> value{0.0};
        phi::floating_point<double> other{value};

        CHECK(value.unsafe() == other.unsafe());
    }
    {
        phi::floating_point<float>       value{0.0f};
        phi::floating_point<long double> other{value};

        CHECK(value.unsafe() == other.unsafe());
    }
    {
        phi::floating_point<double>      value{0.0};
        phi::floating_point<long double> other{value};

        CHECK(value.unsafe() == other.unsafe());
    }
    {
        phi::floating_point<long double> value{0.0};
        phi::floating_point<long double> other{value};

        CHECK(value.unsafe() == other.unsafe());
    }
}

TEST_CASE("core.floating_point.constructor(floating_point&&)")
{
    {
        phi::floating_point<float> value{0.0f};
        phi::floating_point<float> other{phi::move(value)};

        CHECK(value.unsafe() == other.unsafe());
    }
    {
        phi::floating_point<float>  value{0.0f};
        phi::floating_point<double> other{phi::move(value)};

        CHECK(value.unsafe() == other.unsafe());
    }
    {
        phi::floating_point<double> value{0.0};
        phi::floating_point<double> other{phi::move(value)};

        CHECK(value.unsafe() == other.unsafe());
    }
    {
        phi::floating_point<float>       value{0.0f};
        phi::floating_point<long double> other{phi::move(value)};

        CHECK(value.unsafe() == other.unsafe());
    }
    {
        phi::floating_point<double>      value{0.0};
        phi::floating_point<long double> other{phi::move(value)};

        CHECK(value.unsafe() == other.unsafe());
    }
    {
        phi::floating_point<long double> value{0.0};
        phi::floating_point<long double> other{phi::move(value)};

        CHECK(value.unsafe() == other.unsafe());
    }
}

TEST_CASE("core.floating_point.operator==(const floating_point&)")
{
    {
        phi::floating_point<float> value{0.0f};
        phi::floating_point<float> other{1.0f};

        other = value;

        CHECK(value.unsafe() == other.unsafe());
    }
    {
        phi::floating_point<float>  value{0.0f};
        phi::floating_point<double> other{1.0f};

        other = value;

        CHECK(value.unsafe() == other.unsafe());
    }
    {
        phi::floating_point<double> value{0.0f};
        phi::floating_point<double> other{1.0f};

        other = value;

        CHECK(value.unsafe() == other.unsafe());
    }
    {
        phi::floating_point<float>       value{0.0f};
        phi::floating_point<long double> other{1.0f};

        other = value;

        CHECK(value.unsafe() == other.unsafe());
    }
    {
        phi::floating_point<double>      value{0.0f};
        phi::floating_point<long double> other{1.0f};

        other = value;

        CHECK(value.unsafe() == other.unsafe());
    }
    {
        phi::floating_point<long double> value{0.0f};
        phi::floating_point<long double> other{1.0f};

        other = value;

        CHECK(value.unsafe() == other.unsafe());
    }
}

TEST_CASE("core.floating_point.operator==(floating_point&&)")
{
    {
        phi::floating_point<float> value{0.0f};
        phi::floating_point<float> other{1.0f};

        other = phi::move(value);

        CHECK(value.unsafe() == other.unsafe());
    }
    {
        phi::floating_point<float>  value{0.0f};
        phi::floating_point<double> other{1.0f};

        other = phi::move(value);

        CHECK(value.unsafe() == other.unsafe());
    }
    {
        phi::floating_point<double> value{0.0f};
        phi::floating_point<double> other{1.0f};

        other = phi::move(value);

        CHECK(value.unsafe() == other.unsafe());
    }
    {
        phi::floating_point<float>       value{0.0f};
        phi::floating_point<long double> other{1.0f};

        other = phi::move(value);

        CHECK(value.unsafe() == other.unsafe());
    }
    {
        phi::floating_point<double>      value{0.0f};
        phi::floating_point<long double> other{1.0f};

        other = phi::move(value);

        CHECK(value.unsafe() == other.unsafe());
    }
    {
        phi::floating_point<long double> value{0.0f};
        phi::floating_point<long double> other{1.0f};

        other = phi::move(value);

        CHECK(value.unsafe() == other.unsafe());
    }
}

TEST_CASE("core.floating_point.swap")
{
    {
        phi::floating_point<float> value1{1.0f};
        phi::floating_point<float> value2{2.0f};

        value1.swap(value2);

        CHECK(value1.unsafe() == 2.0f);
        CHECK(value2.unsafe() == 1.0f);

        value2.swap(value1);

        CHECK(value1.unsafe() == 1.0f);
        CHECK(value2.unsafe() == 2.0f);

        phi::swap(value1, value2);

        CHECK(value1.unsafe() == 2.0f);
        CHECK(value2.unsafe() == 1.0f);

        phi::swap(value1, value2);

        CHECK(value1.unsafe() == 1.0f);
        CHECK(value2.unsafe() == 2.0f);
    }
    {
        phi::floating_point<double> value1{1.0};
        phi::floating_point<double> value2{2.0};

        value1.swap(value2);

        CHECK(value1.unsafe() == 2.0);
        CHECK(value2.unsafe() == 1.0);

        value2.swap(value1);

        CHECK(value1.unsafe() == 1.0);
        CHECK(value2.unsafe() == 2.0);

        phi::swap(value1, value2);

        CHECK(value1.unsafe() == 2.0);
        CHECK(value2.unsafe() == 1.0);

        phi::swap(value1, value2);

        CHECK(value1.unsafe() == 1.0);
        CHECK(value2.unsafe() == 2.0);
    }
    {
        phi::floating_point<long double> value1{1.0L};
        phi::floating_point<long double> value2{2.0L};

        value1.swap(value2);

        CHECK(value1.unsafe() == 2.0L);
        CHECK(value2.unsafe() == 1.0L);

        value2.swap(value1);

        CHECK(value1.unsafe() == 1.0L);
        CHECK(value2.unsafe() == 2.0L);

        phi::swap(value1, value2);

        CHECK(value1.unsafe() == 2.0L);
        CHECK(value2.unsafe() == 1.0L);

        phi::swap(value1, value2);

        CHECK(value1.unsafe() == 1.0L);
        CHECK(value2.unsafe() == 2.0L);
    }
}
