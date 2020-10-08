#include "SetupDebugReportMode.hpp"
#include <Phi/Core/Assert.hpp>
#include <Phi/Core/Log.hpp>

int main()
{
    SetupDebugReportMode();

    phi::Log::initialize_default_loggers();

    PHI_ASSERT(false, "[ASSERT FAILED]");
}
