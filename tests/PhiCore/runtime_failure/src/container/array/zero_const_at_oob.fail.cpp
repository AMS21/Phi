#include "SetupRuntimeFailure.hpp"
#include <phi/container/array.hpp>

int main()
{
    SetupRuntimeFailure();

    const phi::array<int, 0u> arr{};
    (void)arr.at(0u);
}
