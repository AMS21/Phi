#define PHI_CONFIG_EXTENSIVE_STRING_VIEW_ASSERTS

#include "SetupRuntimeFailure.hpp"

#include <phi/compiler_support/unused.hpp>
#include <phi/compiler_support/warning.hpp>

PHI_GCC_SUPPRESS_WARNING_WITH_PUSH("-Winline")

#include <phi/container/string_view.hpp>

int main()
{
    SetupRuntimeFailure();

    phi::string_view view("a", 3u);
    PHI_UNUSED_VARIABLE(view);
}

PHI_GCC_SUPPRESS_WARNING_POP()
