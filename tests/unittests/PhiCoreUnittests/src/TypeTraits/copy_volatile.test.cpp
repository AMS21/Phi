#include <catch2/catch_test_macros.hpp>

#include <Phi/TypeTraits/copy_volatile.hpp>
#include <Phi/TypeTraits/is_same.hpp>

TEST_CASE("copy_volatile")
{
    STATIC_REQUIRE(phi::is_same_v<typename phi::copy_volatile<int, float>::type, float>);
    STATIC_REQUIRE(
            phi::is_same_v<typename phi::copy_volatile<volatile int, float>::type, volatile float>);
    STATIC_REQUIRE(
            phi::is_same_v<typename phi::copy_volatile<int, volatile float>::type, volatile float>);
    STATIC_REQUIRE(phi::is_same_v<typename phi::copy_volatile<volatile int, volatile float>::type,
                                  volatile float>);

    STATIC_REQUIRE(
            phi::is_same_v<typename phi::copy_volatile<int, const float>::type, const float>);
    STATIC_REQUIRE(phi::is_same_v<typename phi::copy_volatile<const int, float>::type, float>);
    STATIC_REQUIRE(
            phi::is_same_v<typename phi::copy_volatile<const int, const float>::type, const float>);

    STATIC_REQUIRE(phi::is_same_v<typename phi::copy_volatile<const volatile int, float>::type,
                                  volatile float>);
    STATIC_REQUIRE(phi::is_same_v<typename phi::copy_volatile<int, const volatile float>::type,
                                  const volatile float>);
    STATIC_REQUIRE(phi::is_same_v<
                   typename phi::copy_volatile<const volatile int, const volatile float>::type,
                   const volatile float>);

    STATIC_REQUIRE(phi::is_same_v<typename phi::copy_volatile<volatile int, const float>::type,
                                  const volatile float>);
}

TEST_CASE("copy_volatile_t")
{
    STATIC_REQUIRE(phi::is_same_v<typename phi::copy_volatile_t<int, float>, float>);
    STATIC_REQUIRE(
            phi::is_same_v<typename phi::copy_volatile_t<volatile int, float>, volatile float>);
    STATIC_REQUIRE(
            phi::is_same_v<typename phi::copy_volatile_t<int, volatile float>, volatile float>);
    STATIC_REQUIRE(phi::is_same_v<typename phi::copy_volatile_t<volatile int, volatile float>,
                                  volatile float>);

    STATIC_REQUIRE(phi::is_same_v<typename phi::copy_volatile_t<int, const float>, const float>);
    STATIC_REQUIRE(phi::is_same_v<typename phi::copy_volatile_t<const int, float>, float>);
    STATIC_REQUIRE(
            phi::is_same_v<typename phi::copy_volatile_t<const int, const float>, const float>);

    STATIC_REQUIRE(phi::is_same_v<typename phi::copy_volatile_t<const volatile int, float>,
                                  volatile float>);
    STATIC_REQUIRE(phi::is_same_v<typename phi::copy_volatile_t<int, const volatile float>,
                                  const volatile float>);
    STATIC_REQUIRE(
            phi::is_same_v<typename phi::copy_volatile_t<const volatile int, const volatile float>,
                           const volatile float>);

    STATIC_REQUIRE(phi::is_same_v<typename phi::copy_volatile_t<volatile int, const float>,
                                  const volatile float>);
}
