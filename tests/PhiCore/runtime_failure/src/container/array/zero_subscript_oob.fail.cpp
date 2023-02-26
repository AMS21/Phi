#include "SetupRuntimeFailure.hpp"

#include <phi/container/array.hpp>

int main()
{
    SetupRuntimeFailure();

    phi::array<int, 0u> arr{};
    (void)arr[0u];
}
