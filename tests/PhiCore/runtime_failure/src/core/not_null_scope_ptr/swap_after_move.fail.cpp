#include "SetupRuntimeFailure.hpp"

#include <phi/core/move.hpp>
#include <phi/core/scope_ptr.hpp>

int main()
{
    SetupRuntimeFailure();

    phi::not_null_scope_ptr<int> ptr{new int(21)};
    phi::not_null_scope_ptr<int> moved_to_ptr{phi::move(ptr)};

    ptr.swap(moved_to_ptr);
}
