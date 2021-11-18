#include <Phi/Test/TestMacros.hpp>

#include <Phi/CompilerSupport/Unused.hpp>
#include <Phi/Core/NonCopyable.hpp>
#include <utility>

class A : phi::NonCopyable
{};

TEST_CASE("NonCopyable", "[Core][NonCopyable]")
{
    SECTION("Default constructable")
    {
        A a;
        PHI_UNUSED_PARAMETER(a);
    }

    SECTION("Move constructable")
    {
        A a;

        A b(std::move(a));
        PHI_UNUSED_PARAMETER(b);
    }

    SECTION("Move assignable")
    {
        A a;

        A b = std::move(a);
        PHI_UNUSED_PARAMETER(b);
    }
}
