#include "SetupRuntimeFailure.hpp"
#include <phi/compiler_support/unused.hpp>
#include <phi/core/observer_ptr.hpp>

int main()
{
    SetupRuntimeFailure();

    phi::observer_ptr<int> ptr;

    auto err = *ptr;
    PHI_UNUSED_VARIABLE(err);
}
