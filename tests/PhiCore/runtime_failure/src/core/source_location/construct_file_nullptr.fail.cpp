#include "SetupRuntimeFailure.hpp"

#include <phi/core/source_location.hpp>

int main()
{
    SetupRuntimeFailure();

    phi::source_location loc{nullptr, "function", 1, 1};
}
