#include "SetupRuntimeFailure.hpp"
#include <Phi/Algorithm/StringLength.hpp>
#include <Phi/Config/Warning.hpp>

int main()
{
    SetupRuntimeFailure();

    const char* ptr = nullptr;

    phi::usize length = phi::StringLength(ptr);
    PHI_UNUSED_PARAMETER(length);
}
