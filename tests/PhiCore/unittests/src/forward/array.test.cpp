#include <phi/test/test_macros.hpp>

#include <phi/forward/array.hpp>

TEST_CASE("forward.string_view.forward")
{
    {
        phi::array<int, 21u>* pointer = nullptr;
        CHECK(pointer == nullptr);
    }
}

#include <phi/container/array.hpp>

TEST_CASE("forward.string_view")
{
    phi::array<int, 21u> arr{};
    (void)arr;
}
