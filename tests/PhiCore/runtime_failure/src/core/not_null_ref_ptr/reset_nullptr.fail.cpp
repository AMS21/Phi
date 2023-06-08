#include "SetupRuntimeFailure.hpp"

#include <phi/core/ref_ptr.hpp>

int main()
{
    SetupRuntimeFailure();

    phi::not_null_ref_ptr<int> ptr{new int(21)};
    int*                       raw_ptr = nullptr;

    ptr.reset(raw_ptr);
}
