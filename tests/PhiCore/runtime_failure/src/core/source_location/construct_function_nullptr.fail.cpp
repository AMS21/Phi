#include "SetupRuntimeFailure.hpp"

#include <phi/core/source_location.hpp>

int main()
{
    SetupRuntimeFailure();

    phi::source_location loc{"file", nullptr, 1, 1};
    (void)loc;
}
