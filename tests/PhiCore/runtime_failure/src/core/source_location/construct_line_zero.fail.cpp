#include "SetupRuntimeFailure.hpp"

#include <phi/core/source_location.hpp>

int main()
{
    SetupRuntimeFailure();

    phi::source_location loc{"file", "function", 0, 1};
    (void)loc;
}
