#include "SetupRuntimeFailure.hpp"

#include <phi/compiler_support/unused.hpp>
#include <phi/container/string_view.hpp>

int main()
{
    SetupRuntimeFailure();

    phi::string_view view("a", 3u);
    PHI_UNUSED_VARIABLE(view);
}
