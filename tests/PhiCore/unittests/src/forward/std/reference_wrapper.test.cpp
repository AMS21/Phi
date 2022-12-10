#include <phi/test/test_macros.hpp>

#include <phi/forward/std/reference_wrapper.hpp>

TEST_CASE("forward.std.reference_wrapper.forward")
{
    std::reference_wrapper<int>* pointer = nullptr;

    CHECK(pointer == nullptr);
}

#include <functional>

TEST_CASE("forward.std.reference_wrapper")
{
    int value = 21;

    std::reference_wrapper<int> reference_wrapper{value};

    (void)reference_wrapper;
    (void)value;
}
