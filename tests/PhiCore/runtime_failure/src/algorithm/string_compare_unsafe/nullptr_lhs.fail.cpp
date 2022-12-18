#include "SetupRuntimeFailure.hpp"
#include "phi/core/compare_result.hpp"

#include <phi/algorithm/string_compare_unsafe.hpp>
#include <phi/compiler_support/unused.hpp>

int main()
{
    SetupRuntimeFailure();

    const char* ptr = nullptr;

    phi::CompareResult result = phi::string_compare_unsafe(ptr, "Test");
    PHI_UNUSED_VARIABLE(result);
}
