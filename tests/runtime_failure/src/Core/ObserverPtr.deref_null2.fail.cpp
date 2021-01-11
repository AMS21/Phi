#include "SetupDebugReportMode.hpp"
#include <Phi/Core/ObserverPtr.hpp>

class A
{
public:
    void f()
    {}
};

int main()
{
    SetupDebugReportMode();

    phi::ObserverPtr<A> ptr;

    ptr->f();
}
