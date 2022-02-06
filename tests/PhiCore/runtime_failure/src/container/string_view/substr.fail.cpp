#include "SetupRuntimeFailure.hpp"
#include <phi/compiler_support/unused.hpp>
#include <phi/container/string_view.hpp>

int main()
{
    SetupRuntimeFailure();

    phi::string_view view("test");

    phi::string_view sub = view.substring_view(6u);

    PHI_UNUSED_VARIABLE(sub);
}
