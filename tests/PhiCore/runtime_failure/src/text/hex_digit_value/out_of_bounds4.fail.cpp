#include "SetupRuntimeFailure.hpp"

#include <phi/text/hex_digit_value.hpp>

int main()
{
    SetupRuntimeFailure();

    (void)phi::hex_digit_value('\0');
}
