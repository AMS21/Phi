#include "SetupRuntimeFailure.hpp"

#include <phi/compiler_support/unused.hpp>
#include <phi/compiler_support/warning.hpp>

PHI_GCC_SUPPRESS_WARNING_WITH_PUSH("-Winline")

#include <phi/core/observer_ptr.hpp>

int main()
{
    SetupRuntimeFailure();

    phi::observer_ptr<int> ptr;

    phi::not_null_observer_ptr<int> not_null = ptr.release_not_null();

    PHI_UNUSED_PARAMETER(not_null);
}

PHI_GCC_SUPPRESS_WARNING_POP()
