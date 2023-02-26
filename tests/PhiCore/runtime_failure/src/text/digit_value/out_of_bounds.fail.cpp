#include "SetupRuntimeFailure.hpp"

#include <phi/text/digit_value.hpp>

int main()
{
    SetupRuntimeFailure();

    (void)phi::digit_value('a');
}
