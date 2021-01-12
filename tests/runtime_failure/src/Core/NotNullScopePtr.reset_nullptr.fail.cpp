#include "SetupDebugReportMode.hpp"
#include <Phi/Core/ScopePtr.hpp>

int main()
{
    SetupDebugReportMode();

    phi::NotNullScopePtr<int> ptr(new int(3));

    int* null = nullptr;

    ptr.reset(null);
}
