#include "SetupDebugReportMode.hpp"
#include <Phi/Core/ObserverPtr.hpp>

int main()
{
    SetupDebugReportMode();

    phi::ObserverPtr<int> ptr;

    phi::NotNullObserverPtr<int> not_null = ptr.release_not_null();
}
