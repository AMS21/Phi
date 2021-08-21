#include "SetupRuntimeFailure.hpp"
#include <Phi/Config/Warning.hpp>
#include <Phi/Container/StringView.hpp>

int main()
{
    SetupRuntimeFailure();

    phi::StringView view("a", 3u);
    PHI_UNUSED_VARIABLE(view);
}
