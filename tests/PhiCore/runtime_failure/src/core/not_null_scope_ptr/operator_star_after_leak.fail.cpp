#include "SetupRuntimeFailure.hpp"

#include <phi/core/scope_ptr.hpp>

int main()
{
    SetupRuntimeFailure();

    phi::not_null_scope_ptr<int> ptr{new int(3)};
    (void)ptr.leak_ptr();

    *ptr;
}
