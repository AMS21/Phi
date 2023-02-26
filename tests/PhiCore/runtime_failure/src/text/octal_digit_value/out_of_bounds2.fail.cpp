#include "SetupRuntimeFailure.hpp"

#include <phi/text/octal_digit_value.hpp>

int main()
{
    SetupRuntimeFailure();

    (void)phi::octal_digit_value('9');
}
