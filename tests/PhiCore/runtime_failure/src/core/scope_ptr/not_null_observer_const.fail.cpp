#include "SetupRuntimeFailure.hpp"

#include <phi/core/observer_ptr.hpp>
#include <phi/core/scope_ptr.hpp>

int main()
{
    SetupRuntimeFailure();

    const phi::scope_ptr<int> ptr;

    (void)ptr.not_null_observer();
}
