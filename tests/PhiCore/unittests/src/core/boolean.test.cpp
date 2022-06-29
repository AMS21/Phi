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

#include <phi/test/test_macros.hpp>

#include "constexpr_helper.hpp"
#include <phi/core/boolean.hpp>
#include <phi/core/move.hpp>
#include <phi/type_traits/is_assignable.hpp>
#include <phi/type_traits/is_constructible.hpp>
#include <phi/type_traits/is_default_constructible.hpp>
#include <phi/type_traits/is_standard_layout.hpp>
#include <phi/type_traits/is_trivially_copyable.hpp>
#include <sstream>
#include <string>

TEST_CASE("boolean layout", "[Utility][Types][boolean]")
{
    STATIC_REQUIRE(sizeof(phi::boolean) == sizeof(bool));
#if PHI_HAS_WORKING_IS_TRIVIALLY_COPYABLE()
    STATIC_REQUIRE(phi::is_trivially_copyable<phi::boolean>::value);
#endif
#if PHI_HAS_WORKING_IS_STANDARD_LAYOUT()
    STATIC_REQUIRE(phi::is_standard_layout<phi::boolean>::value);
#endif
#if PHI_HAS_WORKING_IS_DEFAULT_CONSTRUCTIBLE()
    STATIC_REQUIRE_FALSE(phi::is_default_constructible<phi::boolean>::value);
#endif

    // conversion checks
    STATIC_REQUIRE(phi::is_constructible<phi::boolean, bool>::value);
    STATIC_REQUIRE(phi::is_constructible<phi::boolean, phi::boolean>::value);
    STATIC_REQUIRE_FALSE(phi::is_constructible<phi::boolean, int>::value);
    STATIC_REQUIRE_FALSE(phi::is_constructible<phi::boolean, float>::value);
    STATIC_REQUIRE(phi::is_constructible<bool, phi::boolean>::value);

    STATIC_REQUIRE(phi::is_assignable<phi::boolean, bool>::value);
    STATIC_REQUIRE(phi::is_assignable<phi::boolean, phi::boolean>::value);
    STATIC_REQUIRE_FALSE(phi::is_assignable<phi::boolean, int>::value);
    STATIC_REQUIRE_FALSE(phi::is_assignable<phi::boolean, float>::value);
    STATIC_REQUIRE_FALSE(phi::is_assignable<bool, phi::boolean>::value);
}

TEST_CASE("boolean", "[Utility][Types][boolean]")
{
    SECTION("Type traits")
    {
        CHECK_SAME_TYPE(phi::boolean::this_type, phi::boolean);
        CHECK_SAME_TYPE(phi::boolean::limits_type, std::numeric_limits<bool>);
    }

    SECTION("constructor")
    {
        CONSTEXPR_RUNTIME phi::boolean bool1(true);
        STATIC_REQUIRE(static_cast<bool>(bool1));

        CONSTEXPR_RUNTIME phi::boolean bool2(false);
        STATIC_REQUIRE_FALSE(static_cast<bool>(bool2));

        CONSTEXPR_RUNTIME phi::boolean bool3(bool1);
        STATIC_REQUIRE(static_cast<bool>(bool3));

        CONSTEXPR_RUNTIME phi::boolean bool4(phi::move(bool2));
        STATIC_REQUIRE_FALSE(static_cast<bool>(bool4));
    }

    SECTION("assignment")
    {
        phi::boolean bool1(true);
        phi::boolean bool2(false);
        phi::boolean bool3(true);

        bool1 = false;
        CHECK_FALSE(static_cast<bool>(bool1));
        bool1 = true;
        CHECK(static_cast<bool>(bool1));

        bool1 = bool2;
        CHECK_FALSE(static_cast<bool>(bool1));
        bool1 = bool3;
        CHECK(static_cast<bool>(bool1));
    }

    SECTION("negate")
    {
        CONSTEXPR_RUNTIME phi::boolean bool1(true);
        STATIC_REQUIRE_FALSE(!bool1);

        CONSTEXPR_RUNTIME phi::boolean bool2(false);
        STATIC_REQUIRE(!bool2);
    }

    SECTION("comparison")
    {
        CONSTEXPR_RUNTIME phi::boolean bool1(true);
        STATIC_REQUIRE(bool(bool1 == true));
        STATIC_REQUIRE(bool(true == bool1));
        STATIC_REQUIRE(bool(bool1 != false));
        STATIC_REQUIRE(bool(false != bool1));
        STATIC_REQUIRE(bool(bool1 == phi::boolean(true)));
        STATIC_REQUIRE(bool(bool1 != phi::boolean(false)));

        CONSTEXPR_RUNTIME phi::boolean bool2(false);
        STATIC_REQUIRE(bool(bool2 == false));
        STATIC_REQUIRE(bool(false == bool2));
        STATIC_REQUIRE(bool(bool2 != true));
        STATIC_REQUIRE(bool(true != bool2));
        STATIC_REQUIRE(bool(bool2 == phi::boolean(false)));
        STATIC_REQUIRE(bool(bool2 != phi::boolean(true)));
    }

    SECTION("i/o")
    {
        std::ostringstream out_stream;
        std::istringstream in_stream("0");

        phi::boolean boolean(true);
        out_stream << boolean;
        CHECK(out_stream.str() == "1");

        in_stream >> boolean;
        CHECK_FALSE(static_cast<bool>(boolean));
    }

    SECTION("unsafe")
    {
        CONSTEXPR_RUNTIME phi::boolean boolean(true);
        STATIC_REQUIRE(boolean.unsafe());
    }

    SECTION("std::hash")
    {
        phi::size_t true_hash  = std::hash<phi::boolean>{}(true);
        phi::size_t false_hash = std::hash<phi::boolean>{}(false);

        CHECK(true_hash != false_hash);
        CHECK(true_hash == std::hash<bool>{}(true));
        CHECK(false_hash == std::hash<bool>{}(false));
    }
}
