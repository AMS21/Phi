#include "SetupRuntimeFailure.hpp"
#include <phi/core/assert.hpp>

int main()
{
    SetupRuntimeFailure();

    PHI_ASSERT(false, "[ASSERT FAILED]");
}
