#include "SetupRuntimeFailure.hpp"

#include <phi/core/scope_ptr.hpp>

struct A
{
    int val{0};
};

int main()
{
    SetupRuntimeFailure();

    phi::scope_ptr<A> ptr;

    (void)ptr->val;
}
