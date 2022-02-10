#include "SetupRuntimeFailure.hpp"

#include <phi/compiler_support/unused.hpp>
#include <phi/compiler_support/warning.hpp>

PHI_GCC_SUPPRESS_WARNING_WITH_PUSH("-Winline")

#include <phi/core/flat_ptr.hpp>

int main()
{
    SetupRuntimeFailure();

    phi::flat_ptr ptr;

    phi::not_null_flat_ptr not_null = ptr.release_not_null();
    PHI_UNUSED_VARIABLE(not_null);
}

PHI_GCC_SUPPRESS_WARNING_POP()
