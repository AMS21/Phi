#include <phi/test/test_macros.hpp>

#include <phi/forward/observer_ptr.hpp>

TEST_CASE("forward.observer_ptr.forward")
{
    phi::observer_ptr<int>*          ptr  = nullptr;
    phi::not_null_observer_ptr<int>* ptr2 = nullptr;

    CHECK(ptr == nullptr);
    CHECK(ptr2 == nullptr);
}

#include <phi/core/observer_ptr.hpp>

TEST_CASE("forward.observer_ptr")
{
    int i = 42;

    phi::observer_ptr<int>          ptr  = nullptr;
    phi::not_null_observer_ptr<int> ptr2 = &i;

    CHECK(ptr.get() == nullptr);
    CHECK(ptr2.get() == &i);
}
