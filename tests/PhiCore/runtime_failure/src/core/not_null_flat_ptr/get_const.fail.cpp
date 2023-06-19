#include "SetupRuntimeFailure.hpp"

#include <phi/core/flat_ptr.hpp>

struct fake_not_null_flat_ptr
{
    int* ptr;
};

int main()
{
    SetupRuntimeFailure();

    const fake_not_null_flat_ptr fake{nullptr};
    const phi::not_null_flat_ptr ptr = *reinterpret_cast<const phi::not_null_flat_ptr*>(&fake);

    (void)ptr.get();
}
