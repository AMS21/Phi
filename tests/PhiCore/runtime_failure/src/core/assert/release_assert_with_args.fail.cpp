#include "SetupRuntimeFailure.hpp"

#include <phi/core/assert.hpp>

int main()
{
    SetupRuntimeFailure();

    PHI_RELEASE_ASSERT(false, "[DBG ASSERT FAILED]");
}
