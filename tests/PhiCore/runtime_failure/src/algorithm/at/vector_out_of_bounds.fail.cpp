#include "SetupRuntimeFailure.hpp"

#include <phi/algorithm/at.hpp>
#include <vector>

int main()
{
    SetupRuntimeFailure();

    std::vector<int> vec{0, 1};

    (void)phi::at(vec, 12u);
}
