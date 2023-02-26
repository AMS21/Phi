#include "SetupRuntimeFailure.hpp"

#include <phi/container/string_view.hpp>

int main()
{
    SetupRuntimeFailure();

    phi::string_view view;

    (void)view.at(0u);
}
