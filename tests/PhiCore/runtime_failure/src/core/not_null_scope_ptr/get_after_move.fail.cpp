#include "SetupRuntimeFailure.hpp"

#include <phi/core/move.hpp>
#include <phi/core/scope_ptr.hpp>

int main()
{
    SetupRuntimeFailure();

    phi::not_null_scope_ptr<int> ptr1(new int(3));
    phi::not_null_scope_ptr<int> ptr2(phi::move(ptr1));

    // NOLINTNEXTLINE(clang-analyzer-cplusplus.Move)
    (void)ptr1.get();
}
