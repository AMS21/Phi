#include "SetupRuntimeFailure.hpp"
#include <Phi/Core/Assert.hpp>

int main()
{
    SetupRuntimeFailure();

    PHI_DBG_SIMPLE_ASSERT(false, "[DBG SIMPLE ASSERT FAILED]");
}
