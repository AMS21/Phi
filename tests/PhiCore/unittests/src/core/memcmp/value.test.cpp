#include <phi/test/test_macros.hpp>

#include "constexpr_helper.hpp"
#include <phi/compiler_support/constexpr.hpp>
#include <phi/core/memcmp.hpp>

static PHI_CONSTEXPR_AND_CONST int* int_nullptr   = nullptr;
static PHI_CONSTEXPR_AND_CONST int  integer_value = 21;
static PHI_CONSTEXPR_AND_CONST int* int_ptr       = &integer_value;

template <typename TypeT>
PHI_EXTENDED_CONSTEXPR bool test_memcmp_equal(TypeT* lhs, TypeT* rhs, phi::size_t count)
{
    return phi::memcmp(lhs, rhs, count) == 0;
}

template <typename TypeT>
PHI_EXTENDED_CONSTEXPR bool test_memcmp_lhs(TypeT* lhs, TypeT* rhs, phi::size_t count)
{
    return phi::memcmp(lhs, rhs, count) < 0;
}

template <typename TypeT>
PHI_EXTENDED_CONSTEXPR bool test_memcmp_rhs(TypeT* lhs, TypeT* rhs, phi::size_t count)
{
    return phi::memcmp(lhs, rhs, count) > 0;
}

TEST_CASE("memcmp")
{
    // nullptr - nullptr
    EXT_STATIC_REQUIRE(phi::memcmp(nullptr, nullptr, 0) == 0);

    // nullptr - non-nullptr
    EXT_STATIC_REQUIRE(phi::memcmp(nullptr, int_nullptr, 0) == 0);
    EXT_STATIC_REQUIRE(phi::memcmp(nullptr, int_ptr, 0) < 0);
    CHECK(phi::memcmp(nullptr, int_nullptr, 0) == 0);
    CHECK(phi::memcmp(nullptr, int_ptr, 0) < 0);

    // non-nullptr - nullptr
    EXT_STATIC_REQUIRE(phi::memcmp(int_nullptr, nullptr, 0) == 0);
    EXT_STATIC_REQUIRE(phi::memcmp(int_ptr, nullptr, 0) > 0);
    CHECK(phi::memcmp(int_nullptr, nullptr, 0) == 0);
    CHECK(phi::memcmp(int_ptr, nullptr, 0) > 0);

    // Equals (returns 0)
    EXT_STATIC_REQUIRE(phi::memcmp("123456", "123456", 7) == 0);
    EXT_STATIC_REQUIRE(phi::memcmp("", "", 1) == 0);
    EXT_STATIC_REQUIRE(phi::memcmp("abc", "abc", 4) == 0);
    EXT_STATIC_REQUIRE(phi::memcmp("hello", "hello", 6) == 0);
    EXT_STATIC_REQUIRE(phi::memcmp("1234567890", "123456000", 6) == 0);
    EXT_STATIC_REQUIRE(phi::memcmp("hi", "hi", 2) == 0);
    EXT_STATIC_REQUIRE(phi::memcmp("ha", "hb", 1) == 0);

    PHI_EXTENDED_CONSTEXPR bool result1 = test_memcmp_equal("123456", "123456", 7);
    PHI_EXTENDED_CONSTEXPR bool result2 = test_memcmp_equal("123456", "123456", 7);
    PHI_EXTENDED_CONSTEXPR bool result3 = test_memcmp_equal("", "", 1);
    PHI_EXTENDED_CONSTEXPR bool result4 = test_memcmp_equal("abc", "abc", 4);
    PHI_EXTENDED_CONSTEXPR bool result5 = test_memcmp_equal("hello", "hello", 6);
    PHI_EXTENDED_CONSTEXPR bool result6 = test_memcmp_equal("1234567890", "123456000", 6);
    PHI_EXTENDED_CONSTEXPR bool result7 = test_memcmp_equal("hi", "hi", 2);
    PHI_EXTENDED_CONSTEXPR bool result8 = test_memcmp_equal("ha", "hb", 1);
    EXT_STATIC_REQUIRE(result1);
    EXT_STATIC_REQUIRE(result2);
    EXT_STATIC_REQUIRE(result3);
    EXT_STATIC_REQUIRE(result4);
    EXT_STATIC_REQUIRE(result5);
    EXT_STATIC_REQUIRE(result6);
    EXT_STATIC_REQUIRE(result7);
    EXT_STATIC_REQUIRE(result8);

    // left hand side is greater (returns negative value)
    EXT_STATIC_REQUIRE(phi::memcmp("ABC", "abc", 4) < 0);
    EXT_STATIC_REQUIRE(phi::memcmp("123", "124", 4) < 0);
    EXT_STATIC_REQUIRE(phi::memcmp("", "abc", 1) < 0);
    EXT_STATIC_REQUIRE(phi::memcmp("abc", "abd", 4) < 0);
    EXT_STATIC_REQUIRE(phi::memcmp("abc", "zyx", 1) < 0);

    PHI_EXTENDED_CONSTEXPR bool result9  = test_memcmp_lhs("ABC", "abc", 4);
    PHI_EXTENDED_CONSTEXPR bool result10 = test_memcmp_lhs("123", "124", 4);
    PHI_EXTENDED_CONSTEXPR bool result11 = test_memcmp_lhs("", "abc", 1);
    PHI_EXTENDED_CONSTEXPR bool result12 = test_memcmp_lhs("abc", "abd", 4);
    PHI_EXTENDED_CONSTEXPR bool result13 = test_memcmp_lhs("abc", "zyx", 1);
    EXT_STATIC_REQUIRE(result9);
    EXT_STATIC_REQUIRE(result10);
    EXT_STATIC_REQUIRE(result11);
    EXT_STATIC_REQUIRE(result12);
    EXT_STATIC_REQUIRE(result13);

    // right hand side is greater (returns positive value)
    EXT_STATIC_REQUIRE(phi::memcmp("abc", "ABC", 4) > 0);
    EXT_STATIC_REQUIRE(phi::memcmp("124", "123", 4) > 0);
    EXT_STATIC_REQUIRE(phi::memcmp("abc", "", 1) > 0);
    EXT_STATIC_REQUIRE(phi::memcmp("abd", "abc", 4) > 0);
    EXT_STATIC_REQUIRE(phi::memcmp("zyx", "abc", 1) > 0);

    PHI_EXTENDED_CONSTEXPR bool result14 = test_memcmp_rhs("abc", "ABC", 4);
    PHI_EXTENDED_CONSTEXPR bool result15 = test_memcmp_rhs("124", "123", 4);
    PHI_EXTENDED_CONSTEXPR bool result16 = test_memcmp_rhs("abc", "", 1);
    PHI_EXTENDED_CONSTEXPR bool result17 = test_memcmp_rhs("abd", "abc", 4);
    PHI_EXTENDED_CONSTEXPR bool result18 = test_memcmp_rhs("zyx", "abc", 1);
    EXT_STATIC_REQUIRE(result14);
    EXT_STATIC_REQUIRE(result15);
    EXT_STATIC_REQUIRE(result16);
    EXT_STATIC_REQUIRE(result17);
    EXT_STATIC_REQUIRE(result18);
}
