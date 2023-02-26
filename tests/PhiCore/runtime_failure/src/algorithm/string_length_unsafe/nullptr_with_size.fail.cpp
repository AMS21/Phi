#include "SetupRuntimeFailure.hpp"

#include <phi/algorithm/string_length_unsafe.hpp>

int main()
{
    SetupRuntimeFailure();

    const char* ptr = nullptr;

    (void)phi::string_length_unsafe(ptr, 21u);
}
