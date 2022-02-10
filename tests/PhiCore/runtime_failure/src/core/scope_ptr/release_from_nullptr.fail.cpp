#include "SetupRuntimeFailure.hpp"

#include <phi/compiler_support/warning.hpp>

PHI_GCC_SUPPRESS_WARNING_WITH_PUSH("-Winline")

#include <phi/core/scope_ptr.hpp>

int main()
{
    SetupRuntimeFailure();

    phi::scope_ptr<int> ptr;

    phi::not_null_scope_ptr<int> not_null = ptr.release_not_null();
}

PHI_GCC_SUPPRESS_WARNING_POP()
