#include "SetupRuntimeFailure.hpp"

#include <phi/compiler_support/warning.hpp>
#include <phi/core/flat_ptr.hpp>

struct fake_not_null_flat_ptr
{
    int* ptr;
};

PHI_GCC_SUPPRESS_WARNING("-Wstrict-aliasing")

int main()
{
    SetupRuntimeFailure();

    const fake_not_null_flat_ptr fake{nullptr};
    const phi::not_null_flat_ptr ptr = *reinterpret_cast<const phi::not_null_flat_ptr*>(&fake);

    (void)ptr.get();
}
