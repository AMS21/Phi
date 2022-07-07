#include "SetupRuntimeFailure.hpp"

#include <phi/core/types.hpp>
#include <phi/text/octal_digit_value.hpp>

int main()
{
    SetupRuntimeFailure();

    phi::u8 value = phi::octal_digit_value('9');

    return value.unsafe();
}
