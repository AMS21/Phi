#include "SetupRuntimeFailure.hpp"

#include <phi/compiler_support/warning.hpp>
#include <phi/core/assert.hpp>

int main()
{
    SetupRuntimeFailure();

    PHI_CLANG_SUPPRESS_WARNING_WITH_PUSH("-Wgnu-zero-variadic-macro-arguments")
    PHI_ASSERT(false);
    PHI_CLANG_SUPPRESS_WARNING_POP()
}
