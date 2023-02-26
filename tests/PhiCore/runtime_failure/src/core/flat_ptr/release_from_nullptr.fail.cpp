#include "SetupRuntimeFailure.hpp"

#include <phi/compiler_support/unused.hpp>
#include <phi/core/flat_ptr.hpp>

int main()
{
    SetupRuntimeFailure();

    phi::flat_ptr ptr;

    (void)ptr.release_not_null();
}
