#include "SetupRuntimeFailure.hpp"

#include <Phi/Config/Warning.hpp>
#include <Phi/Math/Abs.hpp>
#include <limits>

int main()
{
    SetupRuntimeFailure();

    int val = phi::abs(std::numeric_limits<int>::min());
    PHI_UNUSED_VARIABLE(val);
}
