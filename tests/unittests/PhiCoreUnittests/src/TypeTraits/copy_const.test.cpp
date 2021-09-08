#include <catch2/catch_test_macros.hpp>

#include <Phi/TypeTraits/copy_const.hpp>
#include <Phi/TypeTraits/is_same.hpp>

TEST_CASE("copy_const")
{
    STATIC_REQUIRE(phi::is_same_v<typename phi::copy_const<int, float>::type, float>);
    STATIC_REQUIRE(phi::is_same_v<typename phi::copy_const<volatile int, float>::type, float>);
    STATIC_REQUIRE(
            phi::is_same_v<typename phi::copy_const<int, volatile float>::type, volatile float>);
    STATIC_REQUIRE(phi::is_same_v<typename phi::copy_const<volatile int, volatile float>::type,
                                  volatile float>);

    STATIC_REQUIRE(phi::is_same_v<typename phi::copy_const<int, const float>::type, const float>);
    STATIC_REQUIRE(phi::is_same_v<typename phi::copy_const<const int, float>::type, const float>);
    STATIC_REQUIRE(
            phi::is_same_v<typename phi::copy_const<const int, const float>::type, const float>);

    STATIC_REQUIRE(
            phi::is_same_v<typename phi::copy_const<const volatile int, float>::type, const float>);
    STATIC_REQUIRE(phi::is_same_v<typename phi::copy_const<int, const volatile float>::type,
                                  const volatile float>);
    STATIC_REQUIRE(
            phi::is_same_v<typename phi::copy_const<const volatile int, const volatile float>::type,
                           const volatile float>);

    STATIC_REQUIRE(phi::is_same_v<typename phi::copy_const<const int, volatile float>::type,
                                  const volatile float>);
}

TEST_CASE("copy_const_t")
{
    STATIC_REQUIRE(phi::is_same_v<typename phi::copy_const_t<int, float>, float>);
    STATIC_REQUIRE(phi::is_same_v<typename phi::copy_const_t<volatile int, float>, float>);
    STATIC_REQUIRE(phi::is_same_v<typename phi::copy_const_t<int, volatile float>, volatile float>);
    STATIC_REQUIRE(phi::is_same_v<typename phi::copy_const_t<volatile int, volatile float>,
                                  volatile float>);

    STATIC_REQUIRE(phi::is_same_v<typename phi::copy_const_t<int, const float>, const float>);
    STATIC_REQUIRE(phi::is_same_v<typename phi::copy_const_t<const int, float>, const float>);
    STATIC_REQUIRE(phi::is_same_v<typename phi::copy_const_t<const int, const float>, const float>);

    STATIC_REQUIRE(
            phi::is_same_v<typename phi::copy_const_t<const volatile int, float>, const float>);
    STATIC_REQUIRE(phi::is_same_v<typename phi::copy_const_t<int, const volatile float>,
                                  const volatile float>);
    STATIC_REQUIRE(
            phi::is_same_v<typename phi::copy_const_t<const volatile int, const volatile float>,
                           const volatile float>);

    STATIC_REQUIRE(phi::is_same_v<typename phi::copy_const_t<const int, volatile float>,
                                  const volatile float>);
}
