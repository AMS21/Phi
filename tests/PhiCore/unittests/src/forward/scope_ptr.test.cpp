#include <phi/test/test_macros.hpp>

#include <phi/forward/scope_ptr.hpp>

TEST_CASE("forward.scope_ptr.forward")
{
    phi::scope_ptr<int>*          ptr  = nullptr;
    phi::not_null_scope_ptr<int>* ptr2 = nullptr;

    CHECK(ptr == nullptr);
    CHECK(ptr2 == nullptr);
}

#include <phi/core/scope_ptr.hpp>

TEST_CASE("forward.scope_ptr")
{
    phi::scope_ptr<int>          ptr  = nullptr;
    phi::not_null_scope_ptr<int> ptr2 = new int(42);

    CHECK(ptr.get() == nullptr);
    CHECK(ptr2.get() != nullptr);
}
