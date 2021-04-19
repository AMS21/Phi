#include "SetupRuntimeFailure.hpp"
#include <Phi/Core/ScopePtr.hpp>

int main()
{
    SetupRuntimeFailure();

    phi::NotNullScopePtr<int> ptr(new int(3));

    int* null = nullptr;

    ptr.reset(null);
}
