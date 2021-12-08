#include <phi/test/test_macros.hpp>

#include <phi/compiler_support/unused.hpp>
#include <phi/core/move.hpp>
#include <phi/core/non_copyable.hpp>

class A : phi::non_copyable
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

        A b(phi::move(a));
        PHI_UNUSED_PARAMETER(b);
    }

    SECTION("Move assignable")
    {
        A a;

        A b = phi::move(a);
        PHI_UNUSED_PARAMETER(b);
    }
}
