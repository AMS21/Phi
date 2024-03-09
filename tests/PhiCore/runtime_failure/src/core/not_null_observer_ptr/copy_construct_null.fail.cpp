#include "SetupRuntimeFailure.hpp"

#include <phi/compiler_support/warning.hpp>
#include <phi/core/observer_ptr.hpp>

struct fake_not_null_observer_ptr
{
    int* ptr;
};

PHI_GCC_SUPPRESS_WARNING("-Wstrict-aliasing")

int main()
{
    SetupRuntimeFailure();

    const fake_not_null_observer_ptr      fake{nullptr};
    const phi::not_null_observer_ptr<int> not_null =
            *reinterpret_cast<const phi::not_null_observer_ptr<int>*>(&fake);

    // NOLINTNEXTLINE(performance-unnecessary-copy-initialization)
    phi::not_null_observer_ptr<int> ptr(not_null);
}
