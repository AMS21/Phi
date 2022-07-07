#include "SetupRuntimeFailure.hpp"

#include <phi/core/types.hpp>
#include <phi/text/binary_digit_value.hpp>

int main()
{
    SetupRuntimeFailure();

    phi::u8 value = phi::binary_digit_value('2');

    return value.unsafe();
}
