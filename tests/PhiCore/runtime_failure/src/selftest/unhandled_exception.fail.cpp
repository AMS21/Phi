#include "SetupRuntimeFailure.hpp"

// NOLINTNEXTLINE(bugprone-exception-escape)
int main()
{
    SetupRuntimeFailure();

    throw "Exception which will not be caught";
}
