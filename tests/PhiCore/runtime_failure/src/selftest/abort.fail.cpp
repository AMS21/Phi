#include "SetupRuntimeFailure.hpp"

PHI_EXTERNAL_HEADERS_BEGIN()
#include <cstdlib>
PHI_EXTERNAL_HEADERS_END()

int main()
{
    SetupRuntimeFailure();

    std::abort();
}
