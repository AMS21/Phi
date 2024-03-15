#include <phi/test/test_macros.hpp>

#include "constexpr_helper.hpp"
#include <phi/algorithm/at.hpp>
#include <phi/compiler_support/constexpr.hpp>
#include <phi/container/array.hpp>
#include <initializer_list>

TEST_CASE("At c-array", "[Utility][At]")
{
    PHI_CONSTEXPR char arr[]{"Test String"};

    EXT_STATIC_REQUIRE(phi::at(arr, 0) == 'T');
    EXT_STATIC_REQUIRE(phi::at(arr, 1) == 'e');
    EXT_STATIC_REQUIRE(phi::at(arr, 2) == 's');
    EXT_STATIC_REQUIRE(phi::at(arr, 3) == 't');
    EXT_STATIC_REQUIRE(phi::at(arr, 4) == ' ');
    EXT_STATIC_REQUIRE(phi::at(arr, 5) == 'S');
    EXT_STATIC_REQUIRE(phi::at(arr, 6) == 't');
    EXT_STATIC_REQUIRE(phi::at(arr, 7) == 'r');
    EXT_STATIC_REQUIRE(phi::at(arr, 8) == 'i');
    EXT_STATIC_REQUIRE(phi::at(arr, 9) == 'n');
    EXT_STATIC_REQUIRE(phi::at(arr, 10) == 'g');
    EXT_STATIC_REQUIRE(phi::at(arr, 11) == '\0');

    CHECK(phi::at(arr, 0) == 'T');
    CHECK(phi::at(arr, 1) == 'e');
    CHECK(phi::at(arr, 2) == 's');
    CHECK(phi::at(arr, 3) == 't');
    CHECK(phi::at(arr, 4) == ' ');
    CHECK(phi::at(arr, 5) == 'S');
    CHECK(phi::at(arr, 6) == 't');
    CHECK(phi::at(arr, 7) == 'r');
    CHECK(phi::at(arr, 8) == 'i');
    CHECK(phi::at(arr, 9) == 'n');
    CHECK(phi::at(arr, 10) == 'g');
    CHECK(phi::at(arr, 11) == '\0');
}

TEST_CASE("At container", "[Utility][At]")
{
    phi::array<int, 5> arr{5, 9, 8, 12, 21};

    CHECK(phi::at(arr, 0) == 5);
    CHECK(phi::at(arr, 1) == 9);
    CHECK(phi::at(arr, 2) == 8);
    CHECK(phi::at(arr, 3) == 12);
    CHECK(phi::at(arr, 4) == 21);
}

TEST_CASE("At initializer_list", "[Utility][At]")
{
    std::initializer_list<int> list{0, 1, 2, 3, 4};

    CHECK(phi::at(list, 0) == 0);
    CHECK(phi::at(list, 1) == 1);
    CHECK(phi::at(list, 2) == 2);
    CHECK(phi::at(list, 3) == 3);
    CHECK(phi::at(list, 4) == 4);
}
