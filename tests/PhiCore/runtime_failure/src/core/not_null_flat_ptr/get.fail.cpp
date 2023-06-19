#include "SetupRuntimeFailure.hpp"

#include <phi/core/flat_ptr.hpp>

struct fake_not_null_flat_ptr
{
    int* ptr;
};

int main()
{
    SetupRuntimeFailure();

    fake_not_null_flat_ptr fake{nullptr};
    phi::not_null_flat_ptr ptr = *reinterpret_cast<phi::not_null_flat_ptr*>(&fake);

    (void)ptr.get();
}
