#include "SetupRuntimeFailure.hpp"

#include <phi/core/types.hpp>
#include <phi/text/octal_digit_value.hpp>

int main()
{
    SetupRuntimeFailure();

    return phi::octal_digit_value('a').unsafe();
}
