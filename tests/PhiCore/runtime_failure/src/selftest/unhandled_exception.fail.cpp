#include "SetupRuntimeFailure.hpp"

// NOLINTNEXTLINE(bugprone-exception-escape)
int main()
{
    SetupRuntimeFailure();

    // NOLINTNEXTLINE(hicpp-exception-baseclass)
    throw "Exception which will not be caught";
}
