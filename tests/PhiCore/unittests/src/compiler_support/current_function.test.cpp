#include <phi/test/test_macros.hpp>

#include <phi/algorithm/string_length.hpp>
#include <phi/compiler_support/current_function.hpp>
#include <phi/compiler_support/extended_attributes.hpp>

PHI_EXTERNAL_HEADERS_BEGIN()
#include <string>
PHI_EXTERNAL_HEADERS_END()

PHI_ATTRIBUTE_CONST const char* function_with_an_interesting_name()
{
    return PHI_CURRENT_FUNCTION();
}

TEST_CASE("CurrentFunction", "[Config][CurrentFunction]")
{
    // General use
    const char* func_name = PHI_CURRENT_FUNCTION();

    CHECK(bool(phi::string_length(func_name) > 0u));

    // Actually includes the function name at some point. Where depends on the compiler
    std::string interesting_func_name = function_with_an_interesting_name();

    CHECK(interesting_func_name.find("function_with_an_interesting_name") != std::string::npos);
}
