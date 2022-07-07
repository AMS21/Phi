#include "SetupRuntimeFailure.hpp"

#include <phi/core/types.hpp>
#include <phi/text/hex_digit_value.hpp>

int main()
{
    SetupRuntimeFailure();

    phi::u8 value = phi::hex_digit_value('G');

    return value.unsafe();
}
