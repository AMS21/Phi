#include "SetupRuntimeFailure.hpp"

#include <phi/algorithm/string_compare_unsafe.hpp>

int main()
{
    SetupRuntimeFailure();

    const char* ptr  = nullptr;
    const char* ptr2 = nullptr;

    (void)phi::string_compare_unsafe(ptr, ptr2);
}
