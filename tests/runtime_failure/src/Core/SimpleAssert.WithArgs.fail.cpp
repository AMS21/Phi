#include "SetupRuntimeFailure.hpp"
#include <Phi/Core/Assert.hpp>

int main()
{
    SetupRuntimeFailure();

    PHI_SIMPLE_ASSERT(false, "[SIMPLE ASSERT FAILED]");
}
