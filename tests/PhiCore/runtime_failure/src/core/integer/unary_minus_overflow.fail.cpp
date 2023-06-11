#include "SetupRuntimeFailure.hpp"

#include <phi/core/integer.hpp>

int main()
{
    SetupRuntimeFailure();

    phi::integer<int> value = phi::integer<int>::min();

    (void)-value;
}
