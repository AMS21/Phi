#include "SetupRuntimeFailure.hpp"
#include <phi/container/array.hpp>

int main()
{
    SetupRuntimeFailure();

    phi::array<int, 3u> arr{1, 2, 3};
    (void)arr[3u];
}
