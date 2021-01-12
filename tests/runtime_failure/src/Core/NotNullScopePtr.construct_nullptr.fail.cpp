#include "SetupDebugReportMode.hpp"
#include <Phi/Core/ScopePtr.hpp>

int main()
{
    SetupDebugReportMode();

    int* null_ptr = nullptr;

    phi::NotNullScopePtr<int> ptr(null_ptr);
}
