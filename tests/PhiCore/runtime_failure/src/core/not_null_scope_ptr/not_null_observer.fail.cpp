#include "SetupRuntimeFailure.hpp"

#include <phi/core/observer_ptr.hpp>
#include <phi/core/scope_ptr.hpp>

int main()
{
    SetupRuntimeFailure();

    phi::not_null_scope_ptr<int> ptr{new int(21)};

    (void)ptr.leak_ptr();
    (void)ptr.not_null_observer();
}
