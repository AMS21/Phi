#include "SetupRuntimeFailure.hpp"

#include <phi/core/integer.hpp>

int main()
{
    SetupRuntimeFailure();

    phi::integer<int> value = 1;

    value %= 0;
}
