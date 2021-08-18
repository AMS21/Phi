#include <catch2/catch_template_test_macros.hpp>

#include <Phi/Math/Abs.hpp>
#include <limits>

TEMPLATE_TEST_CASE("Abs signed", "[Math][Abs]", char, signed char, short, int, long, long long)
{
    STATIC_REQUIRE(phi::abs(TestType(0)) == TestType(0));
    STATIC_REQUIRE(phi::abs(TestType(1)) == TestType(1));
    STATIC_REQUIRE(phi::abs(TestType(-1)) == TestType(1));
    STATIC_REQUIRE(phi::abs(TestType(21)) == TestType(21));
    STATIC_REQUIRE(phi::abs(TestType(-21)) == TestType(21));

    STATIC_REQUIRE(phi::abs(std::numeric_limits<TestType>::min() + TestType(1)) ==
                   std::numeric_limits<TestType>::max());
    STATIC_REQUIRE(phi::abs(std::numeric_limits<TestType>::max()) ==
                   std::numeric_limits<TestType>::max());
}

TEMPLATE_TEST_CASE("Abs unsigned", "[Math][Abs]", unsigned char, unsigned short, unsigned,
                   unsigned long, unsigned long long)
{
    STATIC_REQUIRE(phi::abs(TestType(0)) == TestType(0));
    STATIC_REQUIRE(phi::abs(TestType(1)) == TestType(1));
    STATIC_REQUIRE(phi::abs(TestType(21)) == TestType(21));

    STATIC_REQUIRE(phi::abs(std::numeric_limits<TestType>::min()) == TestType(0));
    STATIC_REQUIRE(phi::abs(std::numeric_limits<TestType>::max()) ==
                   std::numeric_limits<TestType>::max());
}
