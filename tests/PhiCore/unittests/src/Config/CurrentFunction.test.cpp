#include <Phi/Test/TestMacros.hpp>

#include <Phi/Algorithm/StringLength.hpp>
#include <Phi/Config/CurrentFunction.hpp>
#include <string>

const char* function_with_an_interesting_name()
{
    return PHI_CURRENT_FUNCTION();
}

TEST_CASE("CurrentFunction", "[Config][CurrentFunction]")
{
    // General use
    const char* func_name = PHI_CURRENT_FUNCTION();

    CHECK(bool(phi::StringLength(func_name) > 0u));

    // Actually includes the function name at some point. Where depends on the compiler
    std::string interesting_func_name = function_with_an_interesting_name();

    CHECK(interesting_func_name.find("function_with_an_interesting_name") != std::string::npos);
}
