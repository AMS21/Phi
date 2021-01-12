#include "SetupDebugReportMode.hpp"
#include <Phi/Core/ScopePtr.hpp>

int main()
{
    SetupDebugReportMode();

    phi::ScopePtr<int> ptr;

    phi::NotNullScopePtr<int> not_null = ptr.release_not_null();
}
