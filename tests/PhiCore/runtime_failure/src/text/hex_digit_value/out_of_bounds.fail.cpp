#include "SetupRuntimeFailure.hpp"

#include <phi/core/types.hpp>
#include <phi/text/hex_digit_value.hpp>

int main()
{
    SetupRuntimeFailure();

    return phi::hex_digit_value('G').unsafe();
}
