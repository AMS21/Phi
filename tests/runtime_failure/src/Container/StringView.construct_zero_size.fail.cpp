#include "SetupRuntimeFailure.hpp"
#include <Phi/Config/Warning.hpp>
#include <Phi/Container/StringView.hpp>

int main()
{
    SetupRuntimeFailure();

    phi::StringView view("Hello World", 0u);
    PHI_UNUSED_VARIABLE(view);
}
