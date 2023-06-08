#include "SetupRuntimeFailure.hpp"

#include <phi/core/observer_ptr.hpp>

int main()
{
    SetupRuntimeFailure();

    int                             raw_ptr = 21;
    phi::not_null_observer_ptr<int> ptr{&raw_ptr};

    int* integer_nullptr = nullptr;
    ptr.reset(integer_nullptr);
}
