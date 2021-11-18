#include "SetupRuntimeFailure.hpp"

int main()
{
    SetupRuntimeFailure();

    throw "Exception which will not be caught";
}
