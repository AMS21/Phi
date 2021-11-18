#include "SetupRuntimeFailure.hpp"
#include <Phi/Core/Assert.hpp>

int main()
{
    SetupRuntimeFailure();

    PHI_ASSERT(false, "[ASSERT FAILED]");
}
