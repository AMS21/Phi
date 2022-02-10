#include "SetupRuntimeFailure.hpp"

#include <phi/compiler_support/unused.hpp>
#include <phi/compiler_support/warning.hpp>

PHI_GCC_SUPPRESS_WARNING_WITH_PUSH("-Winline")

#include <phi/algorithm/string_length.hpp>

int main()
{
    SetupRuntimeFailure();

    const char* ptr = nullptr;

    phi::usize length = phi::string_length(ptr);
    PHI_UNUSED_VARIABLE(length);
}

PHI_GCC_SUPPRESS_WARNING_POP()
