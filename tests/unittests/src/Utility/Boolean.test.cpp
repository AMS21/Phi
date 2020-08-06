// This file is heavily inspired by Jonathan Müllers <jonathanmueller.dev@gmail.com> type_safe library https://github.com/foonathan/type_safe
// licensed under the MIT license https://github.com/foonathan/type_safe/blob/master/LICENSE
// Original file at https://github.com/foonathan/type_safe/blob/master/include/type_safe/boolean.hpp
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
#include "Phi/Utility/Boolean.hpp"
#include <catch2/catch.hpp>
#include <sstream>
#include <type_traits>
#include <utility>

TEST_CASE("Boolean layout", "[Utility][Types][Boolean]")
{
    STATIC_REQUIRE(sizeof(phi::Boolean) == sizeof(bool));
    STATIC_REQUIRE(std::is_trivially_copyable_v<phi::Boolean>);
    STATIC_REQUIRE(std::is_standard_layout_v<phi::Boolean>);
    STATIC_REQUIRE_FALSE(std::is_default_constructible_v<phi::Boolean>);

    // conversion checks
    STATIC_REQUIRE(std::is_constructible_v<phi::Boolean, bool>);
    STATIC_REQUIRE(std::is_constructible_v<phi::Boolean, phi::Boolean>);
    STATIC_REQUIRE_FALSE(std::is_constructible_v<phi::Boolean, int>);
    STATIC_REQUIRE_FALSE(std::is_constructible_v<phi::Boolean, float>);

    STATIC_REQUIRE(std::is_assignable_v<phi::Boolean, bool>);
    STATIC_REQUIRE(std::is_assignable_v<phi::Boolean, phi::Boolean>);
    STATIC_REQUIRE_FALSE(std::is_assignable_v<phi::Boolean, int>);
    STATIC_REQUIRE_FALSE(std::is_assignable_v<phi::Boolean, float>);
}

TEST_CASE("Boolean", "[Utility][Types][Boolean]")
{
    SECTION("constructor")
    {
        CONSTEXPR_RUNTIME phi::Boolean B1(true);
        STATIC_REQUIRE(static_cast<bool>(B1));

        CONSTEXPR_RUNTIME phi::Boolean B2(false);
        STATIC_REQUIRE_FALSE(static_cast<bool>(B2));

        CONSTEXPR_RUNTIME phi::Boolean B3(B1);
        STATIC_REQUIRE(static_cast<bool>(B3));

        CONSTEXPR_RUNTIME phi::Boolean B4(std::move(B2));
        STATIC_REQUIRE_FALSE(static_cast<bool>(B4));
    }

    SECTION("assignment")
    {
        phi::Boolean b1(true);
        phi::Boolean b2(false);
        phi::Boolean b3(true);

        b1 = false;
        CHECK_FALSE(static_cast<bool>(b1));
        b1 = true;
        CHECK(static_cast<bool>(b1));

        b1 = b2;
        CHECK_FALSE(static_cast<bool>(b1));
        b1 = b3;
        CHECK(static_cast<bool>(b1));
    }

    SECTION("negate")
    {
        CONSTEXPR_RUNTIME phi::Boolean B1(true);
        STATIC_REQUIRE_FALSE(!B1);

        CONSTEXPR_RUNTIME phi::Boolean B2(false);
        STATIC_REQUIRE(!B2);
    }

    SECTION("comparison")
    {
        CONSTEXPR_RUNTIME phi::Boolean B1(true);
        STATIC_REQUIRE(B1 == true);
        STATIC_REQUIRE(true == B1);
        STATIC_REQUIRE(B1 != false);
        STATIC_REQUIRE(false != B1);
        STATIC_REQUIRE(B1 == phi::Boolean(true));
        STATIC_REQUIRE(B1 != phi::Boolean(false));

        CONSTEXPR_RUNTIME phi::Boolean B2(false);
        STATIC_REQUIRE(B2 == false);
        STATIC_REQUIRE(false == B2);
        STATIC_REQUIRE(B2 != true);
        STATIC_REQUIRE(true != B2);
        STATIC_REQUIRE(B2 == phi::Boolean(false));
        STATIC_REQUIRE(B2 != phi::Boolean(true));
    }

    SECTION("i/o")
    {
        std::ostringstream out;
        std::istringstream in("0");

        phi::Boolean b(true);
        out << b;
        CHECK(out.str() == "1");

        in >> b;
        CHECK_FALSE(static_cast<bool>(b));
    }

    SECTION("get")
    {
        CONSTEXPR_RUNTIME phi::Boolean B(true);
        STATIC_REQUIRE(B.get());
    }
}
