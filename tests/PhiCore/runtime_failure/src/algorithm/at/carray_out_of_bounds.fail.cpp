#include "SetupRuntimeFailure.hpp"

#include <phi/algorithm/at.hpp>

int main()
{
    SetupRuntimeFailure();

    char arr[]{"abc"};

    (void)phi::at(arr, 5u);
}
