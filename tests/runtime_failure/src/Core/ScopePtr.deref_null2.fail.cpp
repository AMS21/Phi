#include "SetupDebugReportMode.hpp"
#include <Phi/Core/ScopePtr.hpp>

struct A
{
    void f()
    {}
};

int main()
{
    SetupDebugReportMode();

    phi::ScopePtr<A> ptr;

    ptr->f();
}
