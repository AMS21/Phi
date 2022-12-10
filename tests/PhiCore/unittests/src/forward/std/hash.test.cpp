#include <phi/test/test_macros.hpp>

#include <phi/forward/std/hash.hpp>

TEST_CASE("forward.std.hash.forward")
{
    std::hash<int>* pointer = nullptr;

    CHECK(pointer == nullptr);
}

#include <functional>

TEST_CASE("forward.std.hash")
{
    std::hash<int> hash;

    (void)hash;
}
