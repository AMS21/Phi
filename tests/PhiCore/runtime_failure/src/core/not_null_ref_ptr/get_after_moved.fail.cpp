#include "SetupRuntimeFailure.hpp"

#include <phi/core/ref_ptr.hpp>

int main()
{
    SetupRuntimeFailure();

    phi::not_null_ref_ptr<int> ptr{new int(21)};
    phi::not_null_ref_ptr<int> ptr2{phi::move(ptr)};

    (void)ptr.get();
}
