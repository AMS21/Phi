#include "SetupRuntimeFailure.hpp"
#include <phi/algorithm/string_length.hpp>
#include <phi/compiler_support/unused.hpp>

int main()
{
    SetupRuntimeFailure();

    const char* ptr = nullptr;

    phi::usize length = phi::string_length(ptr);
    PHI_UNUSED_VARIABLE(length);
}
