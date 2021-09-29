#include "SetupRuntimeFailure.hpp"
#include <Phi/CompilerSupport/Unused.hpp>
#include <Phi/Core/ScopePtr.hpp>

int main()
{
    SetupRuntimeFailure();

    phi::NotNullScopePtr<int> ptr(new int(3));

    int* leak_ptr = ptr.leak_ptr();

    delete leak_ptr;

    int* err_ptr = ptr.get();

    PHI_UNUSED_PARAMETER(err_ptr);
}
