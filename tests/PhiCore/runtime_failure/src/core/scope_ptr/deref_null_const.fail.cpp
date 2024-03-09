#include "SetupRuntimeFailure.hpp"

#include <phi/core/scope_ptr.hpp>

int main()
{
    SetupRuntimeFailure();

    const phi::scope_ptr<int> ptr;

    (void)*ptr;
}
