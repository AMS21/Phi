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

    const fake_not_null_observer_ptr fake{nullptr};
    phi::not_null_observer_ptr<int>  not_null =
            *reinterpret_cast<const phi::not_null_observer_ptr<int>*>(&fake);

    int                             value = 21;
    phi::not_null_observer_ptr<int> other{&value};

    other.swap(not_null);
}
