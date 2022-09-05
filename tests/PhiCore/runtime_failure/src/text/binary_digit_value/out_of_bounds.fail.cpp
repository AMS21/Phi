#include "SetupRuntimeFailure.hpp"

#include <phi/core/types.hpp>
#include <phi/text/binary_digit_value.hpp>

int main()
{
    SetupRuntimeFailure();

    return phi::binary_digit_value('a').unsafe();
}
