#include "SetupRuntimeFailure.hpp"
#include <Phi/CompilerSupport/Unused.hpp>
#include <Phi/Core/ScopePtr.hpp>

int main()
{
    SetupRuntimeFailure();

    phi::ScopePtr<int> ptr;

    int val = *ptr;

    PHI_UNUSED_VARIABLE(val);
}
