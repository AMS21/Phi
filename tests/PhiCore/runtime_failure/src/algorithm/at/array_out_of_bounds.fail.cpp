#include "SetupRuntimeFailure.hpp"

#include <phi/algorithm/at.hpp>
#include <phi/container/array.hpp>

int main()
{
    SetupRuntimeFailure();

    phi::array<int, 2u> arr{0, 1};

    (void)phi::at(arr, 3u);
}
