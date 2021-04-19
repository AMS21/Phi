#include "SetupRuntimeFailure.hpp"
#include <Phi/Core/ObserverPtr.hpp>

class A
{
public:
    void f()
    {}
};

int main()
{
    SetupRuntimeFailure();

    phi::ObserverPtr<A> ptr;

    ptr->f();
}
