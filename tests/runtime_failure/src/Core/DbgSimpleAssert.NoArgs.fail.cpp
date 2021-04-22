#include "SetupRuntimeFailure.hpp"
#include <Phi/Config/Warning.hpp>
#include <Phi/Core/Assert.hpp>

int main()
{
    SetupRuntimeFailure();

    PHI_CLANG_SUPPRESS_WARNING_WITH_PUSH("-Wgnu-zero-variadic-macro-arguments")
    PHI_DBG_SIMPLE_ASSERT(false);
    PHI_CLANG_SUPPRESS_WARNING_POP()
}
