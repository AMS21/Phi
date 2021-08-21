#include "SetupRuntimeFailure.hpp"
#include <Phi/Config/Warning.hpp>
#include <Phi/Container/StringView.hpp>

int main()
{
    SetupRuntimeFailure();

    phi::StringView view("test");

    char c = view[6u];
    PHI_UNUSED_VARIABLE(c);
}
