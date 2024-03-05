#include <phi/test/test_macros.hpp>

#include <phi/forward/std/pair.hpp>

TEST_CASE("forward.std.pair.forward")
{
    std::pair<int, int>* pointer = nullptr;

    CHECK(pointer == nullptr);
}

#include <utility>

TEST_CASE("forward.std.forward")
{
    std::pair<int, int> pair;

    (void)pair;
}
