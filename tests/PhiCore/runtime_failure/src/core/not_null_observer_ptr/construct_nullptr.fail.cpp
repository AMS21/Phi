#include "SetupRuntimeFailure.hpp"

#include <phi/core/observer_ptr.hpp>

int main()
{
    SetupRuntimeFailure();

    int*                            raw_ptr = nullptr;
    phi::not_null_observer_ptr<int> ptr{raw_ptr};
}
