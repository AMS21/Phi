#include "SetupRuntimeFailure.hpp"

#include <phi/core/flat_ptr.hpp>

int main()
{
    SetupRuntimeFailure();

    int                    integer = 12;
    int*                   null    = nullptr;
    phi::not_null_flat_ptr ptr(&integer);

    ptr = null;
}
