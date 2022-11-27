#include "SetupRuntimeFailure.hpp"

PHI_EXTERNAL_HEADERS_BEGIN()
#include <exception>
PHI_EXTERNAL_HEADERS_END()

int main()
{
    SetupRuntimeFailure();

    std::terminate();
}
