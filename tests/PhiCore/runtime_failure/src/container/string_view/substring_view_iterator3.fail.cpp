#include "SetupRuntimeFailure.hpp"

#include <phi/container/string_view.hpp>

int main()
{
    SetupRuntimeFailure();

    phi::string_view view("test");

    (void)view.substring_view(view.end(), view.begin());
}
