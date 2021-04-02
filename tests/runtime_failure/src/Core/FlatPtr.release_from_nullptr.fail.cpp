#include "Phi/Config/Warning.hpp"
#include "SetupDebugReportMode.hpp"
#include <Phi/Config/Warning.hpp>
#include <Phi/Core/FlatPtr.hpp>

int main()
{
    SetupDebugReportMode();

    phi::FlatPtr ptr;

    phi::NotNullFlatPtr not_null = ptr.release_not_null();
    PHI_UNUSED_PARAMETER(not_null);
}
