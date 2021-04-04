#include <catch2/catch_test_macros.hpp>

#include <Phi/Config/Warning.hpp>
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
