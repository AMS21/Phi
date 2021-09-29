#include "SetupRuntimeFailure.hpp"
#include <Phi/CompilerSupport/Unused.hpp>
#include <Phi/Core/ObserverPtr.hpp>

int main()
{
    SetupRuntimeFailure();

    phi::ObserverPtr<int> ptr;

    phi::NotNullObserverPtr<int> not_null = ptr.release_not_null();

    PHI_UNUSED_PARAMETER(not_null);
}
