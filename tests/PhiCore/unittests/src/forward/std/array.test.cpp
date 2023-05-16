#include <phi/test/test_macros.hpp>

#include <phi/forward/std/array.hpp>

TEST_CASE("forward.std.array.forward")
{
    std::array<int, 3u>* pointer = nullptr;

    CHECK(pointer == nullptr);
}

#include <array>

TEST_CASE("forward.std.array")
{
    std::array<int, 3u> array{1, 2, 3};
    std::array<int, 0u> array_zero{};

    (void)array;
    (void)array_zero;
}
