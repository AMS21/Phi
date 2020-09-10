#include "SetupDebugReportMode.hpp"
#include <Phi/Utility/Assert.hpp>
#include <Phi/Utility/Log.hpp>

int main()
{
    SetupDebugReportMode();

    phi::Log::InitializeDefaultLoggers();

    PHI_DBG_ASSERT(false);
}
