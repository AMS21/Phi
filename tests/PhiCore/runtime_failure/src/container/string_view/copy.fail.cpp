#include "SetupRuntimeFailure.hpp"
#include <phi/compiler_support/warning.hpp>
#include <phi/container/string_view.hpp>

int main()
{
    SetupRuntimeFailure();

    phi::string_view view("test");
    char             dest[10u] = "";

    view.copy(dest, 10u, 6u);
}
