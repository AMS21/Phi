#include "SetupRuntimeFailure.hpp"

#include <phi/core/scope_ptr.hpp>

int main()
{
    SetupRuntimeFailure();

    int* null_ptr = nullptr;

    phi::not_null_scope_ptr<int> ptr(new int(12));

    ptr = null_ptr;
}
