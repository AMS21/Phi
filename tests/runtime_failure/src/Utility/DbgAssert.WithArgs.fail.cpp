#include "SetupDebugReportMode.hpp"
#include <Phi/Utility/Assert.hpp>
#include <Phi/Utility/Log.hpp>

int main()
{
    SetupDebugReportMode();

    phi::Log::initialize_default_loggers();

    PHI_DBG_ASSERT(false, "[DBG ASSERT FAILED]");
}
