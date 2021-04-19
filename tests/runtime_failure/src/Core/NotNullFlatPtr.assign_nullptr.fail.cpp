#include "SetupRuntimeFailure.hpp"
#include <Phi/Core/FlatPtr.hpp>

int main()
{
    SetupRuntimeFailure();

    int                 i    = 12;
    int*                null = nullptr;
    phi::NotNullFlatPtr ptr(&i);

    ptr = null;
}
