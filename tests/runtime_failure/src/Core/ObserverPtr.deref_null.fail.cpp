#include "SetupRuntimeFailure.hpp"
#include <Phi/CompilerSupport/Unused.hpp>
#include <Phi/Core/ObserverPtr.hpp>

int main()
{
    SetupRuntimeFailure();

    phi::ObserverPtr<int> ptr;

    auto err = *ptr;
    PHI_UNUSED_VARIABLE(err);
}
