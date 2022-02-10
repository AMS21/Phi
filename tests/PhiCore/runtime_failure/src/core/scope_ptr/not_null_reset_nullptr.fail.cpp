#include "SetupRuntimeFailure.hpp"
#include <phi/compiler_support/warning.hpp>

PHI_GCC_SUPPRESS_WARNING_WITH_PUSH("-Winline")

#include <phi/core/scope_ptr.hpp>

int main()
{
    SetupRuntimeFailure();

    phi::not_null_scope_ptr<int> ptr(new int(3));

    int* null = nullptr;

    ptr.reset(null);
}

PHI_GCC_SUPPRESS_WARNING_POP()
