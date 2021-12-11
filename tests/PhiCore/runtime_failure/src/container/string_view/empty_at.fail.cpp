#include "SetupRuntimeFailure.hpp"
#include <phi/compiler_support/unused.hpp>
#include <phi/container/string_view.hpp>

int main()
{
    SetupRuntimeFailure();

    phi::string_view view;

    char c = view.at(0u);
    PHI_UNUSED_VARIABLE(c);
}