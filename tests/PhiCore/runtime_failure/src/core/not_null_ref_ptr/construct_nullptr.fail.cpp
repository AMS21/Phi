#include "SetupRuntimeFailure.hpp"

#include <phi/core/ref_ptr.hpp>

int main()
{
    SetupRuntimeFailure();

    int*                       raw_ptr = nullptr;
    phi::not_null_ref_ptr<int> ptr{raw_ptr};
}
