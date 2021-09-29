#include "SetupRuntimeFailure.hpp"
#include <Phi/Core/Assert.hpp>

int main()
{
    SetupRuntimeFailure();

    PHI_DBG_ASSERT(false, "[DBG ASSERT FAILED]");
}
