#include "SetupRuntimeFailure.hpp"

#include <phi/core/observer_ptr.hpp>
#include <phi/core/ref_ptr.hpp>

int main()
{
    SetupRuntimeFailure();

    phi::ref_ptr<int> ptr;

    (void)ptr.not_null_observer();
}
