#include "SetupRuntimeFailure.hpp"
#include <phi/compiler_support/warning.hpp>

PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Winline")

#include <phi/core/flat_ptr.hpp>

int main()
{
    SetupRuntimeFailure();

    int                    i    = 12;
    int*                   null = nullptr;
    phi::not_null_flat_ptr ptr(&i);

    ptr = null;
}

PHI_GCC_SUPPRESS_WARNING_POP()
