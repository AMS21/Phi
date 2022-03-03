#include "SetupRuntimeFailure.hpp"

#include <phi/core/observer_ptr.hpp>

int main()
{
    SetupRuntimeFailure();

    int                             i    = 12;
    int*                            null = nullptr;
    phi::not_null_observer_ptr<int> ptr(&i);

    ptr = null;
}
