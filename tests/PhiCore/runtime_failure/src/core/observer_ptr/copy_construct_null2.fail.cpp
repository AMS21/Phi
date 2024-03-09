#include "SetupRuntimeFailure.hpp"

#include <phi/compiler_support/warning.hpp>
#include <phi/core/observer_ptr.hpp>

struct Base
{};

struct Derived : public Base
{};

struct fake_not_null_observer_ptr
{
    Derived* ptr;
};

PHI_GCC_SUPPRESS_WARNING("-Wstrict-aliasing")

int main()
{
    SetupRuntimeFailure();

    const fake_not_null_observer_ptr          fake{nullptr};
    const phi::not_null_observer_ptr<Derived> not_null =
            *reinterpret_cast<const phi::not_null_observer_ptr<Derived>*>(&fake);

    phi::observer_ptr<Base> ptr(not_null);
}
