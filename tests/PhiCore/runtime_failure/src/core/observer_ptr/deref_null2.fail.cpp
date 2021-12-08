#include "SetupRuntimeFailure.hpp"
#include <phi/core/observer_ptr.hpp>

struct A
{
    int val{0};
};

int main()
{
    SetupRuntimeFailure();

    phi::observer_ptr<A> ptr;

    return ptr->val;
}
