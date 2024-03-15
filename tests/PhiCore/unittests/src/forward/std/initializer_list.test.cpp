#include <phi/test/test_macros.hpp>

#include <phi/forward/std/initializer_list.hpp>

TEST_CASE("forward.std.initializer_list.forward")
{
    std::initializer_list<int>* pointer = nullptr;

    CHECK(pointer == nullptr);
}

#include <initializer_list>

TEST_CASE("forward.initializer_list.hash")
{
    std::initializer_list<int> init_list;

    (void)init_list;
}
