#include "SetupRuntimeFailure.hpp"
#include <phi/compiler_support/unused.hpp>
#include <phi/core/scope_ptr.hpp>

int main()
{
    SetupRuntimeFailure();

    phi::not_null_scope_ptr<int> ptr(new int(3));

    int* leak_ptr = ptr.leak_ptr();

    delete leak_ptr;

    int* err_ptr = ptr.get();

    PHI_UNUSED_PARAMETER(err_ptr);
}
