#include "SetupRuntimeFailure.hpp"

#include <phi/compiler_support/warning.hpp>
#include <phi/core/observer_ptr.hpp>

struct A
{
    int val{0};
};

struct fake_not_null_observer_ptr
{
    A* ptr;
};

PHI_GCC_SUPPRESS_WARNING("-Wstrict-aliasing")

int main()
{
    SetupRuntimeFailure();

    const fake_not_null_observer_ptr    fake{nullptr};
    const phi::not_null_observer_ptr<A> not_null =
            *reinterpret_cast<const phi::not_null_observer_ptr<A>*>(&fake);

    (void)not_null->val;
}
