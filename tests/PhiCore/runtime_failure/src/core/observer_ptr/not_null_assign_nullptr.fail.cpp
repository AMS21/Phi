#include "SetupRuntimeFailure.hpp"

#include <phi/compiler_support/warning.hpp>

PHI_GCC_SUPPRESS_WARNING_WITH_PUSH("-Winline")

#include <phi/core/observer_ptr.hpp>

int main()
{
    SetupRuntimeFailure();

    int                             i    = 12;
    int*                            null = nullptr;
    phi::not_null_observer_ptr<int> ptr(&i);

    ptr = null;
}

PHI_GCC_SUPPRESS_WARNING_POP()
