#include "SetupDebugReportMode.hpp"
#include <Phi/Core/ScopePtr.hpp>

int main()
{
    SetupDebugReportMode();

    int* null_ptr = nullptr;

    phi::NotNullScopePtr<int> ptr(new int(12));

    ptr = null_ptr;
}
