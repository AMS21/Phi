#include <catch2/catch_test_macros.hpp>

#define CHECK_NOEXCEPT(...) STATIC_REQUIRE(noexcept(__VA_ARGS__))

#define CHECK_NOT_NOEXCEPT(...) STATIC_REQUIRE_FALSE(noexcept(__VA_ARGS__))
