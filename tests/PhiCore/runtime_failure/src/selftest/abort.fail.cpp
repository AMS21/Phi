#include "SetupRuntimeFailure.hpp"

#include <cstdlib>

int main()
{
    SetupRuntimeFailure();

    std::abort();
}
