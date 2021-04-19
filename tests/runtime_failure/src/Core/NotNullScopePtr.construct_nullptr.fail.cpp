#include "SetupRuntimeFailure.hpp"
#include <Phi/Core/ScopePtr.hpp>

int main()
{
    SetupRuntimeFailure();

    int* null_ptr = nullptr;

    phi::NotNullScopePtr<int> ptr(null_ptr);
}
