#include "SetupRuntimeFailure.hpp"
#include <Phi/Core/ScopePtr.hpp>

struct A
{
    int val{0};
};

int main()
{
    SetupRuntimeFailure();

    phi::ScopePtr<A> ptr;

    return ptr->val;
}
