#include "SetupRuntimeFailure.hpp"

#include <phi/core/types.hpp>
#include <phi/text/digit_value.hpp>

int main()
{
    SetupRuntimeFailure();

    return phi::digit_value('a').unsafe();
}
