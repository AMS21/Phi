#include "SetupRuntimeFailure.hpp"
#include <Phi/Config/Warning.hpp>
#include <Phi/Core/ScopePtr.hpp>

int main()
{
    SetupRuntimeFailure();

    phi::ScopePtr<int> ptr;

    int val = *ptr;

    PHI_UNUSED_PARAMETER(val);
}
