#include "SetupRuntimeFailure.hpp"

#include <phi/core/ref_ptr.hpp>

int main()
{
    SetupRuntimeFailure();

    const phi::ref_ptr<int> ptr;

    (void)*ptr;
}
