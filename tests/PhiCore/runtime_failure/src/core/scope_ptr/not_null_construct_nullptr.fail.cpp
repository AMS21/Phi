#include "SetupRuntimeFailure.hpp"
#include <phi/compiler_support/warning.hpp>

PHI_GCC_SUPPRESS_WARNING_WITH_PUSH("-Winline")

#include <phi/core/scope_ptr.hpp>

int main()
{
    SetupRuntimeFailure();

    int* null_ptr = nullptr;

    phi::not_null_scope_ptr<int> ptr(null_ptr);
}

PHI_GCC_SUPPRESS_WARNING_POP()
