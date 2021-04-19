#include "SetupRuntimeFailure.hpp"
#include <Phi/Core/ScopePtr.hpp>

struct A
{
    void f()
    {}
};

int main()
{
    SetupRuntimeFailure();

    phi::ScopePtr<A> ptr;

    ptr->f();
}
