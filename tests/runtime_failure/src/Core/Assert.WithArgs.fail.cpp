#include "SetupRuntimeFailure.hpp"
#include <Phi/Core/Assert.hpp>
#include <Phi/Core/Log.hpp>

int main()
{
    SetupRuntimeFailure();

    phi::Log::initialize_default_loggers();

    PHI_ASSERT(false, "[ASSERT FAILED]");
}
