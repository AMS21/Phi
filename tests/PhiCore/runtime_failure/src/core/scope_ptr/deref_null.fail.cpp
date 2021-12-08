#include "SetupRuntimeFailure.hpp"
#include <phi/compiler_support/unused.hpp>
#include <phi/core/scope_ptr.hpp>

int main()
{
    SetupRuntimeFailure();

    phi::scope_ptr<int> ptr;

    int val = *ptr;

    PHI_UNUSED_VARIABLE(val);
}
