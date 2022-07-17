#include "SetupRuntimeFailure.hpp"
#include <phi/core/assert.hpp>

int main()
{
    SetupRuntimeFailure();

    PHI_RELEASE_ASSERT_NOT_REACHED();
}
