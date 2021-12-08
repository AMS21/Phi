#include "SetupRuntimeFailure.hpp"
#include <phi/core/assert.hpp>

int main()
{
    SetupRuntimeFailure();

    PHI_DBG_ASSERT_NOT_REACHED();
}
