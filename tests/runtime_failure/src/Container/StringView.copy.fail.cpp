#include "SetupRuntimeFailure.hpp"
#include <Phi/Config/Warning.hpp>
#include <Phi/Container/StringView.hpp>

int main()
{
    SetupRuntimeFailure();

    phi::StringView view("test");
    char            dest[10u] = "";

    view.copy(dest, 10u, 6u);
}
