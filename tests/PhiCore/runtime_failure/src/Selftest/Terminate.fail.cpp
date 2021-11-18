#include "SetupRuntimeFailure.hpp"
#include <exception>

int main()
{
    SetupRuntimeFailure();

    std::terminate();
}
