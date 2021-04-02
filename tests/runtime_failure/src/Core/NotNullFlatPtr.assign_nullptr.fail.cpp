#include "SetupDebugReportMode.hpp"
#include <Phi/Core/FlatPtr.hpp>

int main()
{
    SetupDebugReportMode();

    int                 i    = 12;
    int*                null = nullptr;
    phi::NotNullFlatPtr ptr(&i);

    ptr = null;
}
