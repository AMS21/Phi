#include "SetupRuntimeFailure.hpp"
#include <Phi/CompilerSupport/Unused.hpp>
#include <Phi/Container/StringView.hpp>

int main()
{
    SetupRuntimeFailure();

    phi::StringView view("test");

    phi::StringView sub = view.substr(6u);

    PHI_UNUSED_VARIABLE(sub);
}
