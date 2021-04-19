#include "SetupRuntimeFailure.hpp"
#include <Phi/Core/ScopePtr.hpp>

int main()
{
    SetupRuntimeFailure();

    phi::ScopePtr<int> ptr;

    phi::NotNullScopePtr<int> not_null = ptr.release_not_null();
}
