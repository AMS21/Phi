#include "SetupRuntimeFailure.hpp"
#include <Phi/Config/Warning.hpp>
#include <Phi/Core/Assert.hpp>
#include <Phi/Core/Log.hpp>

int main()
{
    SetupRuntimeFailure();

    phi::Log::initialize_default_loggers();

    PHI_CLANG_SUPPRESS_WARNING_WITH_PUSH("-Wgnu-zero-variadic-macro-arguments")
    PHI_ASSERT(false);
    PHI_CLANG_SUPPRESS_WARNING_POP()
}
