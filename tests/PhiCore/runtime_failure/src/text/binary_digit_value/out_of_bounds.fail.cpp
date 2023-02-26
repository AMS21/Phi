#include "SetupRuntimeFailure.hpp"

#include <phi/text/binary_digit_value.hpp>

int main()
{
    SetupRuntimeFailure();

    (void)phi::binary_digit_value('a');
}
