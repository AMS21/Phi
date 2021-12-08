#include "SetupRuntimeFailure.hpp"
#include <phi/core/scope_ptr.hpp>

int main()
{
    SetupRuntimeFailure();

    phi::scope_ptr<int> ptr;

    phi::not_null_scope_ptr<int> not_null = ptr.release_not_null();
}
