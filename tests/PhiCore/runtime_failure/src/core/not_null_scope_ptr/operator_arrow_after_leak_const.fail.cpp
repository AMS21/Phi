#include "SetupRuntimeFailure.hpp"

#include <phi/core/scope_ptr.hpp>

struct A
{
    void test() const
    {}
};

int main()
{
    SetupRuntimeFailure();

    const phi::not_null_scope_ptr<A> ptr{new A()};

    ptr->test();

    // NOTE: Ugly hack around the language and compiler preventing us from doing something stupid
    (void)const_cast<phi::not_null_scope_ptr<A>*>(&ptr)->leak_ptr();
    ptr->test();
}
