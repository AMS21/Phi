#include "SetupRuntimeFailure.hpp"
#include <Phi/Core/ObserverPtr.hpp>

struct A
{
    int val{0};
};

int main()
{
    SetupRuntimeFailure();

    phi::ObserverPtr<A> ptr;

    return ptr->val;
}
