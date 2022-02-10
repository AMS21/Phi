#include "SetupRuntimeFailure.hpp"

#include <phi/compiler_support/unused.hpp>
#include <phi/compiler_support/warning.hpp>

PHI_GCC_SUPPRESS_WARNING_WITH_PUSH("-Winline")

#include <phi/core/scope_ptr.hpp>

int main()
{
    SetupRuntimeFailure();

    phi::not_null_scope_ptr<int> ptr1(new int(3));
    phi::not_null_scope_ptr<int> ptr2(std::move(ptr1));

    int* err_ptr = ptr1.get();

    PHI_UNUSED_VARIABLE(err_ptr);
}

PHI_GCC_SUPPRESS_WARNING_POP()
