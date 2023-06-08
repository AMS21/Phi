#include "SetupRuntimeFailure.hpp"

#include <phi/core/ref_ptr.hpp>

struct A
{
    int val{0};
};

int main()
{
    SetupRuntimeFailure();

    phi::ref_ptr<A> ptr;

    (void)ptr->val;
}
