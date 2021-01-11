#include "SetupDebugReportMode.hpp"
#include <Phi/Core/Assert.hpp>

int main()
{
    SetupDebugReportMode();

    PHI_ASSERT_NOT_REACHED();
}
