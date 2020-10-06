#include <catch2/catch.hpp>

#include <Phi/Utility/At.hpp>
#include <array>
#include <deque>
#include <vector>

TEST_CASE("At c-array", "[Utility][At]")
{
    constexpr char arr[]{"Test String"};

    STATIC_REQUIRE(phi::at(arr, 0) == 'T');
    STATIC_REQUIRE(phi::at(arr, 1) == 'e');
    STATIC_REQUIRE(phi::at(arr, 2) == 's');
    STATIC_REQUIRE(phi::at(arr, 3) == 't');
    STATIC_REQUIRE(phi::at(arr, 4) == ' ');
    STATIC_REQUIRE(phi::at(arr, 5) == 'S');
    STATIC_REQUIRE(phi::at(arr, 6) == 't');
    STATIC_REQUIRE(phi::at(arr, 7) == 'r');
    STATIC_REQUIRE(phi::at(arr, 8) == 'i');
    STATIC_REQUIRE(phi::at(arr, 9) == 'n');
    STATIC_REQUIRE(phi::at(arr, 10) == 'g');
    STATIC_REQUIRE(phi::at(arr, 11) == '\0');
}

TEST_CASE("At container", "[Utility][At]")
{
    SECTION("std::vector")
    {
        std::vector<int> vec{0, 1, 2, 3, 4};

        CHECK(phi::at(vec, 0) == 0);
        CHECK(phi::at(vec, 1) == 1);
        CHECK(phi::at(vec, 2) == 2);
        CHECK(phi::at(vec, 3) == 3);
        CHECK(phi::at(vec, 4) == 4);
    }

    SECTION("std::array")
    {
        std::array<int, 5> arr{5, 9, 8, 12, 21};

        CHECK(phi::at(arr, 0) == 5);
        CHECK(phi::at(arr, 1) == 9);
        CHECK(phi::at(arr, 2) == 8);
        CHECK(phi::at(arr, 3) == 12);
        CHECK(phi::at(arr, 4) == 21);
    }

    SECTION("std::deque")
    {
        std::deque<int> queue{17, -5, 3, 1, 4};

        CHECK(phi::at(queue, 0) == 17);
        CHECK(phi::at(queue, 1) == -5);
        CHECK(phi::at(queue, 2) == 3);
        CHECK(phi::at(queue, 3) == 1);
        CHECK(phi::at(queue, 4) == 4);
    }
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
