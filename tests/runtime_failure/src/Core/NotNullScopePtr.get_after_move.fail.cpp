#include "SetupRuntimeFailure.hpp"
#include <Phi/CompilerSupport/Unused.hpp>
#include <Phi/Core/ScopePtr.hpp>

int main()
{
    SetupRuntimeFailure();

    phi::NotNullScopePtr<int> ptr1(new int(3));
    phi::NotNullScopePtr<int> ptr2(std::move(ptr1));

    int* err_ptr = ptr1.get();

    PHI_UNUSED_VARIABLE(err_ptr);
}
