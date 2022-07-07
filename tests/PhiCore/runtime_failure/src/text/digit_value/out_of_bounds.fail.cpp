#include "SetupRuntimeFailure.hpp"

#include <phi/core/types.hpp>
#include <phi/text/digit_value.hpp>

int main()
{
    SetupRuntimeFailure();

    phi::u8 value = phi::digit_value('a');

    return value.unsafe();
}
