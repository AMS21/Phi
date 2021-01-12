#include "SetupDebugReportMode.hpp"
#include <Phi/Config/Warning.hpp>
#include <Phi/Core/ScopePtr.hpp>

int main()
{
    SetupDebugReportMode();

    phi::NotNullScopePtr<int> ptr(new int(3));

    int* leak_ptr = ptr.leak_ptr();

    delete leak_ptr;

    int* err_ptr = ptr.get();

    PHI_UNUSED_PARAMETER(err_ptr);
}
