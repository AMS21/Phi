#include "SetupRuntimeFailure.hpp"
#include <Phi/CompilerSupport/Unused.hpp>
#include <Phi/Container/StringView.hpp>

int main()
{
    SetupRuntimeFailure();

    phi::StringView view("Hello World", 0u);
    PHI_UNUSED_VARIABLE(view);
}
