#include "SetupDebugReportMode.hpp"
#include <Phi/Core/ObserverPtr.hpp>

int main()
{
    SetupDebugReportMode();

    int                          i    = 12;
    int*                         null = nullptr;
    phi::NotNullObserverPtr<int> ptr(&i);

    ptr = null;
}
