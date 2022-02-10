#include "SetupRuntimeFailure.hpp"

#include <phi/compiler_support/warning.hpp>

PHI_GCC_SUPPRESS_WARNING_WITH_PUSH("-Winline")

#include <phi/container/string_view.hpp>

int main()
{
    SetupRuntimeFailure();

    const char* ptr = nullptr;

    phi::string_view view(ptr);
}

PHI_GCC_SUPPRESS_WARNING_POP()
