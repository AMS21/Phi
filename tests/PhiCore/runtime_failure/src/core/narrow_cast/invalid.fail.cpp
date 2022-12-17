#include "SetupRuntimeFailure.hpp"

#include <phi/core/narrow_cast.hpp>
#include <phi/core/sized_types.hpp>

int main()
{
    SetupRuntimeFailure();

    phi::int32_t large = 999;
    // 999 is to large to be represented in an int8_t
    phi::int8_t small = phi::narrow_cast<phi::int8_t>(large);

    return small;
}
