#include "SetupRuntimeFailure.hpp"

#include <phi/algorithm/string_equals.hpp>

int main()
{
    SetupRuntimeFailure();

    (void)phi::string_equals("", "", 0u);
}
