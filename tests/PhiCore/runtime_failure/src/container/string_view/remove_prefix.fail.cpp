#include "SetupRuntimeFailure.hpp"
#include <phi/container/string_view.hpp>

int main()
{
    SetupRuntimeFailure();

    phi::string_view view("test");

    view.remove_prefix(6u);
}
