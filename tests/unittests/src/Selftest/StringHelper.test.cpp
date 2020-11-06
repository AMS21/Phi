#include <catch2/catch_template_test_macros.hpp>

#include "StringHelper.hpp"

TEMPLATE_TEST_CASE("string_length selftest", "[selftest][StringHelper]", char, unsigned char,
                   signed char)
{
    const TestType* null_str{nullptr};
    CHECK(string_length(null_str) == 0);

    const TestType* str{reinterpret_cast<const TestType*>("test")};
    CHECK(string_length(str) == 4);
}

TEMPLATE_TEST_CASE("string_equals selftest", "[selftest][StringHelper]", char, unsigned char,
                   signed char)
{
    const TestType* null_str{nullptr};
    const TestType* str{reinterpret_cast<const TestType*>("test")};
    const TestType* str2{reinterpret_cast<const TestType*>("testb")};
    const TestType* str3{reinterpret_cast<const TestType*>("tesu")};

    CHECK(string_equals(null_str, null_str));
    CHECK_FALSE(string_equals(null_str, str2));
    CHECK(string_equals(str, str));
    CHECK_FALSE(string_equals(str, str2));
    CHECK_FALSE(string_equals(str, str3));
}
