#include "SetupDebugReportMode.hpp"
#include <Phi/Config/Warning.hpp>
#include <Phi/Core/ObserverPtr.hpp>

int main()
{
    SetupDebugReportMode();

    phi::ObserverPtr<int> ptr;

    auto err = *ptr;
    PHI_UNUSED_PARAMETER(err);
}
