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

    int raw_ptr = 21;

    fake_not_null_flat_ptr fake{nullptr};
    phi::not_null_flat_ptr ptr = *reinterpret_cast<phi::not_null_flat_ptr*>(&fake);
    phi::not_null_flat_ptr ptr2{&raw_ptr};

    ptr2.swap(ptr);
}
