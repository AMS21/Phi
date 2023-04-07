#include <phi/test/test_macros.hpp>

#include <phi/forward/flat_ptr.hpp>

TEST_CASE("forward.flat_ptr.forward")
{
    phi::flat_ptr*          ptr  = nullptr;
    phi::not_null_flat_ptr* ptr2 = nullptr;

    CHECK(ptr == nullptr);
    CHECK(ptr2 == nullptr);
}

#include <phi/core/flat_ptr.hpp>

TEST_CASE("forward.flat_ptr")
{
    int i = 42;

    phi::flat_ptr          ptr  = nullptr;
    phi::not_null_flat_ptr ptr2 = &i;

    CHECK(ptr.get() == nullptr);
    CHECK(ptr2.get() == &i);
}
