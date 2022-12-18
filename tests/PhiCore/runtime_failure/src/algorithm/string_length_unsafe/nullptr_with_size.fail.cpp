#include "SetupRuntimeFailure.hpp"

#include <phi/algorithm/string_length_unsafe.hpp>
#include <phi/compiler_support/unused.hpp>

int main()
{
    SetupRuntimeFailure();

    const char* ptr = nullptr;

    phi::usize length = phi::string_length_unsafe(ptr, 21u);
    PHI_UNUSED_VARIABLE(length);
}
