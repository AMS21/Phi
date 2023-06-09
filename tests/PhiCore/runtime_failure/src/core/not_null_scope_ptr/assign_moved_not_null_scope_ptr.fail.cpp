#include "SetupRuntimeFailure.hpp"

#include <phi/core/scope_ptr.hpp>

int main()
{
    SetupRuntimeFailure();

    phi::not_null_scope_ptr<int> ptr{new int(3)};
    phi::not_null_scope_ptr<int> ptr2{phi::move(ptr)};

    phi::not_null_scope_ptr<int> fail_ptr{new int(21)};

    fail_ptr = phi::move(ptr);
}
