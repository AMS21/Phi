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
#include "Phi/TypeTraits/is_trivially_destructible.hpp"
#include "SameType.hpp"
#include <Phi/Config/Warning.hpp>
#include <Phi/Core/Boolean.hpp>
#include <Phi/Core/Integer.hpp>
#include <Phi/TypeTraits/is_assignable.hpp>
#include <Phi/TypeTraits/is_constructible.hpp>
#include <Phi/TypeTraits/is_convertible.hpp>
#include <Phi/TypeTraits/is_copy_assignable.hpp>
#include <Phi/TypeTraits/is_copy_constructible.hpp>
#include <Phi/TypeTraits/is_default_constructible.hpp>
#include <Phi/TypeTraits/is_move_assignable.hpp>
#include <Phi/TypeTraits/is_move_constructible.hpp>
#include <Phi/TypeTraits/is_nothrow_assignable.hpp>
#include <Phi/TypeTraits/is_nothrow_constructible.hpp>
#include <Phi/TypeTraits/is_nothrow_convertible.hpp>
#include <Phi/TypeTraits/is_nothrow_copy_assignable.hpp>
#include <Phi/TypeTraits/is_nothrow_copy_constructible.hpp>
#include <Phi/TypeTraits/is_nothrow_default_constructible.hpp>
#include <Phi/TypeTraits/is_nothrow_move_assignable.hpp>
#include <Phi/TypeTraits/is_nothrow_move_constructible.hpp>
#include <Phi/TypeTraits/is_same.hpp>
#include <Phi/TypeTraits/is_standard_layout.hpp>
#include <Phi/TypeTraits/is_trivially_copyable.hpp>
#include <cstdint>
#include <limits>
#include <sstream>
#include <string>

template <typename T>
void test_integer_layout()
{
    STATIC_REQUIRE(sizeof(T) == sizeof(typename T::value_type));

    STATIC_REQUIRE(phi::is_standard_layout<T>::value);
    STATIC_REQUIRE(phi::is_trivially_copyable<T>::value);
    STATIC_REQUIRE(phi::is_trivially_destructible<T>::value);

    STATIC_REQUIRE_FALSE(phi::is_default_constructible<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_nothrow_default_constructible<T>::value);
    STATIC_REQUIRE(phi::is_copy_assignable<T>::value);
    STATIC_REQUIRE(phi::is_nothrow_copy_assignable<T>::value);
    STATIC_REQUIRE(phi::is_copy_constructible<T>::value);
    STATIC_REQUIRE(phi::is_nothrow_copy_constructible<T>::value);
    STATIC_REQUIRE(phi::is_move_assignable<T>::value);
    STATIC_REQUIRE(phi::is_nothrow_move_assignable<T>::value);
    STATIC_REQUIRE(phi::is_move_constructible<T>::value);
    STATIC_REQUIRE(phi::is_nothrow_move_constructible<T>::value);
}

template <typename LhsT, typename RhsT>
void test_integer_convertible()
{
    STATIC_REQUIRE(phi::is_constructible<LhsT, RhsT>::value);
    STATIC_REQUIRE(phi::is_nothrow_constructible<LhsT, RhsT>::value);
    STATIC_REQUIRE(phi::is_assignable<LhsT, RhsT>::value);
    STATIC_REQUIRE(phi::is_nothrow_assignable<LhsT, RhsT>::value);
    STATIC_REQUIRE_FALSE(phi::is_convertible<LhsT, RhsT>::value);
    STATIC_REQUIRE_FALSE(phi::is_nothrow_convertible<LhsT, RhsT>::value);

    STATIC_REQUIRE(phi::is_constructible<RhsT, LhsT>::value ==
                   phi::is_same<typename LhsT::value_type, RhsT>::value);
    STATIC_REQUIRE(phi::is_nothrow_constructible<RhsT, LhsT>::value ==
                   phi::is_same<typename LhsT::value_type, RhsT>::value);
    STATIC_REQUIRE(phi::is_convertible<RhsT, LhsT>::value);
    STATIC_REQUIRE(phi::is_nothrow_convertible<RhsT, LhsT>::value);
}

template <typename LhsT, typename RhsT>
void test_integer_not_convertible()
{
    STATIC_REQUIRE_FALSE(phi::is_constructible<LhsT, RhsT>::value);
    STATIC_REQUIRE_FALSE(phi::is_nothrow_constructible<LhsT, RhsT>::value);
    STATIC_REQUIRE_FALSE(phi::is_assignable<LhsT, RhsT>::value);
    STATIC_REQUIRE_FALSE(phi::is_nothrow_assignable<LhsT, RhsT>::value);
    STATIC_REQUIRE_FALSE(phi::is_convertible<LhsT, RhsT>::value);
    STATIC_REQUIRE_FALSE(phi::is_nothrow_convertible<LhsT, RhsT>::value);

    STATIC_REQUIRE_FALSE(phi::is_constructible<RhsT, LhsT>::value);
    STATIC_REQUIRE_FALSE(phi::is_nothrow_constructible<RhsT, LhsT>::value);
    STATIC_REQUIRE_FALSE(phi::is_convertible<RhsT, LhsT>::value);
    STATIC_REQUIRE_FALSE(phi::is_nothrow_convertible<RhsT, LhsT>::value);
}

PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Wuseless-cast")

PHI_CLANG_SUPPRESS_WARNING_PUSH()
PHI_CLANG_SUPPRESS_WARNING("-Wtautological-compare")

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

    test_integer_layout<phi::Integer<std::int8_t>>();
    test_integer_layout<phi::Integer<std::int16_t>>();
    test_integer_layout<phi::Integer<std::int32_t>>();
    test_integer_layout<phi::Integer<std::int64_t>>();

    test_integer_layout<phi::Integer<std::uint8_t>>();
    test_integer_layout<phi::Integer<std::uint16_t>>();
    test_integer_layout<phi::Integer<std::uint32_t>>();
    test_integer_layout<phi::Integer<std::uint64_t>>();
}

TEST_CASE("Integer conversion checks", "[Utility][Types][Integer]")
{
    // std::int8_t
    test_integer_convertible<phi::Integer<std::int8_t>, std::int8_t>();
    test_integer_not_convertible<phi::Integer<std::int8_t>, std::int16_t>();
    test_integer_not_convertible<phi::Integer<std::int8_t>, std::int32_t>();
    test_integer_not_convertible<phi::Integer<std::int8_t>, std::int64_t>();

    test_integer_not_convertible<phi::Integer<std::int8_t>, std::uint8_t>();
    test_integer_not_convertible<phi::Integer<std::int8_t>, std::uint16_t>();
    test_integer_not_convertible<phi::Integer<std::int8_t>, std::uint32_t>();
    test_integer_not_convertible<phi::Integer<std::int8_t>, std::uint64_t>();

    test_integer_not_convertible<phi::Integer<std::int8_t>, bool>();
    test_integer_not_convertible<phi::Integer<std::int8_t>, phi::Boolean>();
    test_integer_not_convertible<phi::Integer<std::int8_t>, char>();
    test_integer_not_convertible<phi::Integer<std::int8_t>, wchar_t>();
    test_integer_not_convertible<phi::Integer<std::int8_t>, char16_t>();
    test_integer_not_convertible<phi::Integer<std::int8_t>, char32_t>();
    test_integer_not_convertible<phi::Integer<std::int8_t>, float>();
    test_integer_not_convertible<phi::Integer<std::int8_t>, double>();
    test_integer_not_convertible<phi::Integer<std::int8_t>, long double>();

    // std::int16_t
    test_integer_convertible<phi::Integer<std::int16_t>, std::int8_t>();
    test_integer_convertible<phi::Integer<std::int16_t>, std::int16_t>();
    test_integer_not_convertible<phi::Integer<std::int16_t>, std::int32_t>();
    test_integer_not_convertible<phi::Integer<std::int16_t>, std::int64_t>();

    test_integer_convertible<phi::Integer<std::int16_t>, std::uint8_t>();
    test_integer_not_convertible<phi::Integer<std::int16_t>, std::uint16_t>();
    test_integer_not_convertible<phi::Integer<std::int16_t>, std::uint32_t>();
    test_integer_not_convertible<phi::Integer<std::int16_t>, std::uint64_t>();

    test_integer_not_convertible<phi::Integer<std::int16_t>, bool>();
    test_integer_not_convertible<phi::Integer<std::int16_t>, phi::Boolean>();
    test_integer_not_convertible<phi::Integer<std::int16_t>, char>();
    test_integer_not_convertible<phi::Integer<std::int16_t>, wchar_t>();
    test_integer_not_convertible<phi::Integer<std::int16_t>, char16_t>();
    test_integer_not_convertible<phi::Integer<std::int16_t>, char32_t>();
    test_integer_not_convertible<phi::Integer<std::int16_t>, float>();
    test_integer_not_convertible<phi::Integer<std::int16_t>, double>();
    test_integer_not_convertible<phi::Integer<std::int16_t>, long double>();

    // std::int32_t
    test_integer_convertible<phi::Integer<std::int32_t>, std::int8_t>();
    test_integer_convertible<phi::Integer<std::int32_t>, std::int16_t>();
    test_integer_convertible<phi::Integer<std::int32_t>, std::int32_t>();
    test_integer_not_convertible<phi::Integer<std::int32_t>, std::int64_t>();

    test_integer_convertible<phi::Integer<std::int32_t>, std::uint8_t>();
    test_integer_convertible<phi::Integer<std::int32_t>, std::uint16_t>();
    test_integer_not_convertible<phi::Integer<std::int32_t>, std::uint32_t>();
    test_integer_not_convertible<phi::Integer<std::int32_t>, std::uint64_t>();

    test_integer_not_convertible<phi::Integer<std::int32_t>, bool>();
    test_integer_not_convertible<phi::Integer<std::int32_t>, phi::Boolean>();
    test_integer_not_convertible<phi::Integer<std::int32_t>, char>();
    test_integer_not_convertible<phi::Integer<std::int32_t>, wchar_t>();
    test_integer_not_convertible<phi::Integer<std::int32_t>, char16_t>();
    test_integer_not_convertible<phi::Integer<std::int32_t>, char32_t>();
    test_integer_not_convertible<phi::Integer<std::int32_t>, float>();
    test_integer_not_convertible<phi::Integer<std::int32_t>, double>();
    test_integer_not_convertible<phi::Integer<std::int32_t>, long double>();

    // std::int64_t
    test_integer_convertible<phi::Integer<std::int64_t>, std::int8_t>();
    test_integer_convertible<phi::Integer<std::int64_t>, std::int16_t>();
    test_integer_convertible<phi::Integer<std::int64_t>, std::int32_t>();
    test_integer_convertible<phi::Integer<std::int64_t>, std::int64_t>();

    test_integer_convertible<phi::Integer<std::int64_t>, std::uint8_t>();
    test_integer_convertible<phi::Integer<std::int64_t>, std::uint16_t>();
    test_integer_convertible<phi::Integer<std::int64_t>, std::uint32_t>();
    test_integer_not_convertible<phi::Integer<std::int64_t>, std::uint64_t>();

    test_integer_not_convertible<phi::Integer<std::int64_t>, bool>();
    test_integer_not_convertible<phi::Integer<std::int64_t>, phi::Boolean>();
    test_integer_not_convertible<phi::Integer<std::int64_t>, char>();
    test_integer_not_convertible<phi::Integer<std::int64_t>, wchar_t>();
    test_integer_not_convertible<phi::Integer<std::int64_t>, char16_t>();
    test_integer_not_convertible<phi::Integer<std::int64_t>, char32_t>();
    test_integer_not_convertible<phi::Integer<std::int64_t>, float>();
    test_integer_not_convertible<phi::Integer<std::int64_t>, double>();
    test_integer_not_convertible<phi::Integer<std::int64_t>, long double>();

    // std::uint8_t
    test_integer_not_convertible<phi::Integer<std::uint8_t>, std::int8_t>();
    test_integer_not_convertible<phi::Integer<std::uint8_t>, std::int16_t>();
    test_integer_not_convertible<phi::Integer<std::uint8_t>, std::int32_t>();
    test_integer_not_convertible<phi::Integer<std::uint8_t>, std::int64_t>();

    test_integer_convertible<phi::Integer<std::uint8_t>, std::uint8_t>();
    test_integer_not_convertible<phi::Integer<std::uint8_t>, std::uint16_t>();
    test_integer_not_convertible<phi::Integer<std::uint8_t>, std::uint32_t>();
    test_integer_not_convertible<phi::Integer<std::uint8_t>, std::uint64_t>();

    test_integer_not_convertible<phi::Integer<std::uint8_t>, bool>();
    test_integer_not_convertible<phi::Integer<std::uint8_t>, phi::Boolean>();
    test_integer_not_convertible<phi::Integer<std::uint8_t>, char>();
    test_integer_not_convertible<phi::Integer<std::uint8_t>, wchar_t>();
    test_integer_not_convertible<phi::Integer<std::uint8_t>, char16_t>();
    test_integer_not_convertible<phi::Integer<std::uint8_t>, char32_t>();
    test_integer_not_convertible<phi::Integer<std::uint8_t>, float>();
    test_integer_not_convertible<phi::Integer<std::uint8_t>, double>();
    test_integer_not_convertible<phi::Integer<std::uint8_t>, long double>();

    // std::uint16_t
    test_integer_not_convertible<phi::Integer<std::uint16_t>, std::int8_t>();
    test_integer_not_convertible<phi::Integer<std::uint16_t>, std::int16_t>();
    test_integer_not_convertible<phi::Integer<std::uint16_t>, std::int32_t>();
    test_integer_not_convertible<phi::Integer<std::uint16_t>, std::int64_t>();

    test_integer_convertible<phi::Integer<std::uint16_t>, std::uint8_t>();
    test_integer_convertible<phi::Integer<std::uint16_t>, std::uint16_t>();
    test_integer_not_convertible<phi::Integer<std::uint16_t>, std::uint32_t>();
    test_integer_not_convertible<phi::Integer<std::uint16_t>, std::uint64_t>();

    test_integer_not_convertible<phi::Integer<std::uint16_t>, bool>();
    test_integer_not_convertible<phi::Integer<std::uint16_t>, phi::Boolean>();
    test_integer_not_convertible<phi::Integer<std::uint16_t>, char>();
    test_integer_not_convertible<phi::Integer<std::uint16_t>, wchar_t>();
    test_integer_not_convertible<phi::Integer<std::uint16_t>, char16_t>();
    test_integer_not_convertible<phi::Integer<std::uint16_t>, char32_t>();
    test_integer_not_convertible<phi::Integer<std::uint16_t>, float>();
    test_integer_not_convertible<phi::Integer<std::uint16_t>, double>();
    test_integer_not_convertible<phi::Integer<std::uint16_t>, long double>();

    // std::uint32_t
    test_integer_not_convertible<phi::Integer<std::uint32_t>, std::int8_t>();
    test_integer_not_convertible<phi::Integer<std::uint32_t>, std::int16_t>();
    test_integer_not_convertible<phi::Integer<std::uint32_t>, std::int32_t>();
    test_integer_not_convertible<phi::Integer<std::uint32_t>, std::int64_t>();

    test_integer_convertible<phi::Integer<std::uint32_t>, std::uint8_t>();
    test_integer_convertible<phi::Integer<std::uint32_t>, std::uint16_t>();
    test_integer_convertible<phi::Integer<std::uint32_t>, std::uint32_t>();
    test_integer_not_convertible<phi::Integer<std::uint32_t>, std::uint64_t>();

    test_integer_not_convertible<phi::Integer<std::uint32_t>, bool>();
    test_integer_not_convertible<phi::Integer<std::uint32_t>, phi::Boolean>();
    test_integer_not_convertible<phi::Integer<std::uint32_t>, char>();
    test_integer_not_convertible<phi::Integer<std::uint32_t>, wchar_t>();
    test_integer_not_convertible<phi::Integer<std::uint32_t>, char16_t>();
    test_integer_not_convertible<phi::Integer<std::uint32_t>, char32_t>();
    test_integer_not_convertible<phi::Integer<std::uint32_t>, float>();
    test_integer_not_convertible<phi::Integer<std::uint32_t>, double>();
    test_integer_not_convertible<phi::Integer<std::uint32_t>, long double>();

    // std::uint64_t
    test_integer_not_convertible<phi::Integer<std::uint64_t>, std::int8_t>();
    test_integer_not_convertible<phi::Integer<std::uint64_t>, std::int16_t>();
    test_integer_not_convertible<phi::Integer<std::uint64_t>, std::int32_t>();
    test_integer_not_convertible<phi::Integer<std::uint64_t>, std::int64_t>();

    test_integer_convertible<phi::Integer<std::uint64_t>, std::uint8_t>();
    test_integer_convertible<phi::Integer<std::uint64_t>, std::uint16_t>();
    test_integer_convertible<phi::Integer<std::uint64_t>, std::uint32_t>();
    test_integer_convertible<phi::Integer<std::uint64_t>, std::uint64_t>();

    test_integer_not_convertible<phi::Integer<std::uint64_t>, bool>();
    test_integer_not_convertible<phi::Integer<std::uint64_t>, phi::Boolean>();
    test_integer_not_convertible<phi::Integer<std::uint64_t>, char>();
    test_integer_not_convertible<phi::Integer<std::uint64_t>, wchar_t>();
    test_integer_not_convertible<phi::Integer<std::uint64_t>, char16_t>();
    test_integer_not_convertible<phi::Integer<std::uint64_t>, char32_t>();
    test_integer_not_convertible<phi::Integer<std::uint64_t>, float>();
    test_integer_not_convertible<phi::Integer<std::uint64_t>, double>();
    test_integer_not_convertible<phi::Integer<std::uint64_t>, long double>();
}

TEST_CASE("Integer", "[Utility][Types][Integer]")
{
    using int_t = phi::Integer<std::int32_t>;

    SECTION("Type traits")
    {
        // this_type
        CHECK_SAME_TYPE(phi::Integer<std::int8_t>::this_type, phi::Integer<std::int8_t>);
        CHECK_SAME_TYPE(phi::Integer<std::int16_t>::this_type, phi::Integer<std::int16_t>);
        CHECK_SAME_TYPE(phi::Integer<std::int32_t>::this_type, phi::Integer<std::int32_t>);
        CHECK_SAME_TYPE(phi::Integer<std::int64_t>::this_type, phi::Integer<std::int64_t>);

        CHECK_SAME_TYPE(phi::Integer<std::uint8_t>::this_type, phi::Integer<std::uint8_t>);
        CHECK_SAME_TYPE(phi::Integer<std::uint16_t>::this_type, phi::Integer<std::uint16_t>);
        CHECK_SAME_TYPE(phi::Integer<std::uint32_t>::this_type, phi::Integer<std::uint32_t>);
        CHECK_SAME_TYPE(phi::Integer<std::uint64_t>::this_type, phi::Integer<std::uint64_t>);

        // value_type
        CHECK_SAME_TYPE(phi::Integer<std::int8_t>::value_type, std::int8_t);
        CHECK_SAME_TYPE(phi::Integer<std::int16_t>::value_type, std::int16_t);
        CHECK_SAME_TYPE(phi::Integer<std::int32_t>::value_type, std::int32_t);
        CHECK_SAME_TYPE(phi::Integer<std::int64_t>::value_type, std::int64_t);

        CHECK_SAME_TYPE(phi::Integer<std::uint8_t>::value_type, std::uint8_t);
        CHECK_SAME_TYPE(phi::Integer<std::uint16_t>::value_type, std::uint16_t);
        CHECK_SAME_TYPE(phi::Integer<std::uint32_t>::value_type, std::uint32_t);
        CHECK_SAME_TYPE(phi::Integer<std::uint64_t>::value_type, std::uint64_t);

        // limits_type
        CHECK_SAME_TYPE(phi::Integer<std::int8_t>::limits_type, std::numeric_limits<std::int8_t>);
        CHECK_SAME_TYPE(phi::Integer<std::int16_t>::limits_type, std::numeric_limits<std::int16_t>);
        CHECK_SAME_TYPE(phi::Integer<std::int32_t>::limits_type, std::numeric_limits<std::int32_t>);
        CHECK_SAME_TYPE(phi::Integer<std::int64_t>::limits_type, std::numeric_limits<std::int64_t>);

        CHECK_SAME_TYPE(phi::Integer<std::uint8_t>::limits_type, std::numeric_limits<std::uint8_t>);
        CHECK_SAME_TYPE(phi::Integer<std::uint16_t>::limits_type,
                        std::numeric_limits<std::uint16_t>);
        CHECK_SAME_TYPE(phi::Integer<std::uint32_t>::limits_type,
                        std::numeric_limits<std::uint32_t>);
        CHECK_SAME_TYPE(phi::Integer<std::uint64_t>::limits_type,
                        std::numeric_limits<std::uint64_t>);
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
        EXT_STATIC_REQUIRE(static_cast<std::int32_t>(-a) == -static_cast<std::int32_t>(a));
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

    SECTION("signed_to_unsigned")
    {
        // From int8_t
        STATIC_REQUIRE_FALSE(
                phi::is_convertible<phi::Integer<int8_t>, phi::Integer<uint8_t>>::value);
        STATIC_REQUIRE_FALSE(
                phi::is_convertible<phi::Integer<int8_t>, phi::Integer<uint16_t>>::value);
        STATIC_REQUIRE_FALSE(
                phi::is_convertible<phi::Integer<int8_t>, phi::Integer<uint32_t>>::value);
        STATIC_REQUIRE_FALSE(
                phi::is_convertible<phi::Integer<int8_t>, phi::Integer<uint64_t>>::value);

        // From int16_t
        STATIC_REQUIRE_FALSE(
                phi::is_convertible<phi::Integer<int16_t>, phi::Integer<uint8_t>>::value);
        STATIC_REQUIRE_FALSE(
                phi::is_convertible<phi::Integer<int16_t>, phi::Integer<uint16_t>>::value);
        STATIC_REQUIRE_FALSE(
                phi::is_convertible<phi::Integer<int16_t>, phi::Integer<uint32_t>>::value);
        STATIC_REQUIRE_FALSE(
                phi::is_convertible<phi::Integer<int16_t>, phi::Integer<uint64_t>>::value);

        // From int32_t
        STATIC_REQUIRE_FALSE(
                phi::is_convertible<phi::Integer<int32_t>, phi::Integer<uint8_t>>::value);
        STATIC_REQUIRE_FALSE(
                phi::is_convertible<phi::Integer<int32_t>, phi::Integer<uint16_t>>::value);
        STATIC_REQUIRE_FALSE(
                phi::is_convertible<phi::Integer<int32_t>, phi::Integer<uint32_t>>::value);
        STATIC_REQUIRE_FALSE(
                phi::is_convertible<phi::Integer<int32_t>, phi::Integer<uint64_t>>::value);

        // From int64_t
        STATIC_REQUIRE_FALSE(
                phi::is_convertible<phi::Integer<int64_t>, phi::Integer<uint8_t>>::value);
        STATIC_REQUIRE_FALSE(
                phi::is_convertible<phi::Integer<int64_t>, phi::Integer<uint16_t>>::value);
        STATIC_REQUIRE_FALSE(
                phi::is_convertible<phi::Integer<int64_t>, phi::Integer<uint32_t>>::value);
        STATIC_REQUIRE_FALSE(
                phi::is_convertible<phi::Integer<int64_t>, phi::Integer<uint64_t>>::value);
    }

    SECTION("unsigned_to_signed")
    {
        // From uint8_t
        STATIC_REQUIRE_FALSE(
                phi::is_convertible<phi::Integer<uint8_t>, phi::Integer<int8_t>>::value);
        STATIC_REQUIRE(phi::is_convertible<phi::Integer<uint8_t>, phi::Integer<int16_t>>::value);
        STATIC_REQUIRE(phi::is_convertible<phi::Integer<uint8_t>, phi::Integer<int32_t>>::value);
        STATIC_REQUIRE(phi::is_convertible<phi::Integer<uint8_t>, phi::Integer<int64_t>>::value);

        // From uint16_t
        STATIC_REQUIRE_FALSE(
                phi::is_convertible<phi::Integer<uint16_t>, phi::Integer<int8_t>>::value);
        STATIC_REQUIRE_FALSE(
                phi::is_convertible<phi::Integer<uint16_t>, phi::Integer<int16_t>>::value);
        STATIC_REQUIRE(phi::is_convertible<phi::Integer<uint16_t>, phi::Integer<int32_t>>::value);
        STATIC_REQUIRE(phi::is_convertible<phi::Integer<uint16_t>, phi::Integer<int64_t>>::value);

        // From uint32_t
        STATIC_REQUIRE_FALSE(
                phi::is_convertible<phi::Integer<uint32_t>, phi::Integer<int8_t>>::value);
        STATIC_REQUIRE_FALSE(
                phi::is_convertible<phi::Integer<uint32_t>, phi::Integer<int16_t>>::value);
        STATIC_REQUIRE_FALSE(
                phi::is_convertible<phi::Integer<uint32_t>, phi::Integer<int32_t>>::value);
        STATIC_REQUIRE(phi::is_convertible<phi::Integer<uint32_t>, phi::Integer<int64_t>>::value);

        // From uint64_t
        STATIC_REQUIRE_FALSE(
                phi::is_convertible<phi::Integer<uint64_t>, phi::Integer<int8_t>>::value);
        STATIC_REQUIRE_FALSE(
                phi::is_convertible<phi::Integer<uint64_t>, phi::Integer<int16_t>>::value);
        STATIC_REQUIRE_FALSE(
                phi::is_convertible<phi::Integer<uint64_t>, phi::Integer<int32_t>>::value);
        STATIC_REQUIRE_FALSE(
                phi::is_convertible<phi::Integer<uint64_t>, phi::Integer<int64_t>>::value);
    }

    SECTION("signed_to_signed")
    {
        // From int8_t
        STATIC_REQUIRE(phi::is_convertible<phi::Integer<int8_t>, phi::Integer<int8_t>>::value);
        STATIC_REQUIRE(phi::is_convertible<phi::Integer<int8_t>, phi::Integer<int16_t>>::value);
        STATIC_REQUIRE(phi::is_convertible<phi::Integer<int8_t>, phi::Integer<int32_t>>::value);
        STATIC_REQUIRE(phi::is_convertible<phi::Integer<int8_t>, phi::Integer<int64_t>>::value);

        // From int16_t
        STATIC_REQUIRE_FALSE(
                phi::is_convertible<phi::Integer<int16_t>, phi::Integer<int8_t>>::value);
        STATIC_REQUIRE(phi::is_convertible<phi::Integer<int16_t>, phi::Integer<int16_t>>::value);
        STATIC_REQUIRE(phi::is_convertible<phi::Integer<int16_t>, phi::Integer<int32_t>>::value);
        STATIC_REQUIRE(phi::is_convertible<phi::Integer<int16_t>, phi::Integer<int64_t>>::value);

        // From int32_t
        STATIC_REQUIRE_FALSE(
                phi::is_convertible<phi::Integer<int32_t>, phi::Integer<int8_t>>::value);
        STATIC_REQUIRE_FALSE(
                phi::is_convertible<phi::Integer<int32_t>, phi::Integer<int16_t>>::value);
        STATIC_REQUIRE(phi::is_convertible<phi::Integer<int32_t>, phi::Integer<int32_t>>::value);
        STATIC_REQUIRE(phi::is_convertible<phi::Integer<int32_t>, phi::Integer<int64_t>>::value);

        // From int64_t
        STATIC_REQUIRE_FALSE(
                phi::is_convertible<phi::Integer<int64_t>, phi::Integer<int8_t>>::value);
        STATIC_REQUIRE_FALSE(
                phi::is_convertible<phi::Integer<int64_t>, phi::Integer<int16_t>>::value);
        STATIC_REQUIRE_FALSE(
                phi::is_convertible<phi::Integer<int64_t>, phi::Integer<int32_t>>::value);
        STATIC_REQUIRE(phi::is_convertible<phi::Integer<int64_t>, phi::Integer<int64_t>>::value);
    }

    SECTION("unsigned_to_unsigned")
    {
        // From uint8_t
        STATIC_REQUIRE(phi::is_convertible<phi::Integer<uint8_t>, phi::Integer<uint8_t>>::value);
        STATIC_REQUIRE(phi::is_convertible<phi::Integer<uint8_t>, phi::Integer<uint16_t>>::value);
        STATIC_REQUIRE(phi::is_convertible<phi::Integer<uint8_t>, phi::Integer<uint32_t>>::value);
        STATIC_REQUIRE(phi::is_convertible<phi::Integer<uint8_t>, phi::Integer<uint64_t>>::value);

        // From uint16_t
        STATIC_REQUIRE_FALSE(
                phi::is_convertible<phi::Integer<uint16_t>, phi::Integer<uint8_t>>::value);
        STATIC_REQUIRE(phi::is_convertible<phi::Integer<uint16_t>, phi::Integer<uint16_t>>::value);
        STATIC_REQUIRE(phi::is_convertible<phi::Integer<uint16_t>, phi::Integer<uint32_t>>::value);
        STATIC_REQUIRE(phi::is_convertible<phi::Integer<uint16_t>, phi::Integer<uint64_t>>::value);

        // From uint32_t
        STATIC_REQUIRE_FALSE(
                phi::is_convertible<phi::Integer<uint32_t>, phi::Integer<uint8_t>>::value);
        STATIC_REQUIRE_FALSE(
                phi::is_convertible<phi::Integer<uint32_t>, phi::Integer<uint16_t>>::value);
        STATIC_REQUIRE(phi::is_convertible<phi::Integer<uint32_t>, phi::Integer<uint32_t>>::value);
        STATIC_REQUIRE(phi::is_convertible<phi::Integer<uint32_t>, phi::Integer<uint64_t>>::value);

        // From uint64_t
        STATIC_REQUIRE_FALSE(
                phi::is_convertible<phi::Integer<uint64_t>, phi::Integer<uint8_t>>::value);
        STATIC_REQUIRE_FALSE(
                phi::is_convertible<phi::Integer<uint64_t>, phi::Integer<uint16_t>>::value);
        STATIC_REQUIRE_FALSE(
                phi::is_convertible<phi::Integer<uint64_t>, phi::Integer<uint32_t>>::value);
        STATIC_REQUIRE(phi::is_convertible<phi::Integer<uint64_t>, phi::Integer<uint64_t>>::value);
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

PHI_CLANG_SUPPRESS_WARNING_POP()
PHI_GCC_SUPPRESS_WARNING_POP()
