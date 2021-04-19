#include "SetupRuntimeFailure.hpp"
#include <Phi/Core/ScopePtr.hpp>

int main()
{
    SetupRuntimeFailure();

    int* null_ptr = nullptr;

    phi::NotNullScopePtr<int> ptr(new int(12));

    ptr = null_ptr;
}
