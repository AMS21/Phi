#include "SetupRuntimeFailure.hpp"

#include <phi/core/observer_ptr.hpp>

struct A
{
    int val{0};
};

int main()
{
    SetupRuntimeFailure();

    const phi::observer_ptr<A> ptr;

    (void)ptr->val;
}
