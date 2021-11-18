#include "SetupRuntimeFailure.hpp"
#include <Phi/CompilerSupport/Unused.hpp>
#include <Phi/Core/FlatPtr.hpp>

int main()
{
    SetupRuntimeFailure();

    phi::FlatPtr ptr;

    phi::NotNullFlatPtr not_null = ptr.release_not_null();
    PHI_UNUSED_VARIABLE(not_null);
}
