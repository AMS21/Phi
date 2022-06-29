#include "SetupRuntimeFailure.hpp"

#include <phi/core/observer_ptr.hpp>

int main()
{
    SetupRuntimeFailure();

    int                             integer = 12;
    int*                            null    = nullptr;
    phi::not_null_observer_ptr<int> ptr(&integer);

    ptr = null;
}
