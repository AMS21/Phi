#include "SetupRuntimeFailure.hpp"

#include <phi/core/scope_ptr.hpp>

struct A
{
    void test()
    {}
};

int main()
{
    SetupRuntimeFailure();

    phi::not_null_scope_ptr<A> ptr{new A()};

    (void)ptr.leak_ptr();
    ptr->test();
}
