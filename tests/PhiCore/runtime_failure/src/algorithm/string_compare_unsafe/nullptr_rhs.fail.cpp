#include "SetupRuntimeFailure.hpp"

#include <phi/algorithm/string_compare_unsafe.hpp>

int main()
{
    SetupRuntimeFailure();

    const char* ptr = nullptr;

    (void)phi::string_compare_unsafe("Test", ptr);
}
