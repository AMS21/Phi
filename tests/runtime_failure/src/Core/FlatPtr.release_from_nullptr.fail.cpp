#include "Phi/Config/Warning.hpp"
#include "SetupRuntimeFailure.hpp"
#include <Phi/Config/Warning.hpp>
#include <Phi/Core/FlatPtr.hpp>

int main()
{
    SetupRuntimeFailure();

    phi::FlatPtr ptr;

    phi::NotNullFlatPtr not_null = ptr.release_not_null();
    PHI_UNUSED_PARAMETER(not_null);
}
