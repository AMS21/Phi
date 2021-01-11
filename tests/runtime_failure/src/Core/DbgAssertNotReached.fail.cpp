#include "SetupDebugReportMode.hpp"
#include <Phi/Core/Assert.hpp>

int main()
{
    SetupDebugReportMode();

    PHI_DBG_ASSERT_NOT_REACHED();
}
