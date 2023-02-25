#include "SetupRuntimeFailure.hpp"

#include <phi/algorithm/at.hpp>
#include <phi/container/array.hpp>

int main()
{
    SetupRuntimeFailure();

    std::initializer_list<int> list{0, 1};

    (void)phi::at(list, 3u);
}
