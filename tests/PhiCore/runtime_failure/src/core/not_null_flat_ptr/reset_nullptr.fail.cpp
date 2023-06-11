#include "SetupRuntimeFailure.hpp"

#include <phi/core/flat_ptr.hpp>

int main()
{
    SetupRuntimeFailure();

    int  integer     = 42;
    int* int_nullptr = nullptr;

    phi::not_null_flat_ptr ptr{&integer};

    ptr.reset(int_nullptr);
}
