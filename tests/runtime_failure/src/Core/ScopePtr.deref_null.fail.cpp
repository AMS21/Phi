#include "SetupDebugReportMode.hpp"
#include <Phi/Config/Warning.hpp>
#include <Phi/Core/ScopePtr.hpp>

int main()
{
    SetupDebugReportMode();

    phi::ScopePtr<int> ptr;

    int val = *ptr;

    PHI_UNUSED_PARAMETER(val);
}
