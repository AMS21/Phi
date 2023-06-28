#include "SetupRuntimeFailure.hpp"

#include <phi/core/observer_ptr.hpp>

int main()
{
    SetupRuntimeFailure();

    phi::observer_ptr<int> ptr;

    (void)ptr.not_null();
}
