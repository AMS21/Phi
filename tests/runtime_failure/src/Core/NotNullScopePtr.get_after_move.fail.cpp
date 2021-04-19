#include "SetupRuntimeFailure.hpp"
#include <Phi/Config/Warning.hpp>
#include <Phi/Core/ScopePtr.hpp>

int main()
{
    SetupRuntimeFailure();

    phi::NotNullScopePtr<int> ptr1(new int(3));
    phi::NotNullScopePtr<int> ptr2(std::move(ptr1));

    int* err_ptr = ptr1.get();

    PHI_UNUSED_PARAMETER(err_ptr);
}
