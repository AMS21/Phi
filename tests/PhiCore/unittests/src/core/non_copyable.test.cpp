#include <phi/test/test_macros.hpp>

#include <phi/compiler_support/unused.hpp>
#include <phi/core/move.hpp>
#include <phi/core/non_copyable.hpp>

struct A : public phi::non_copyable
{};

TEST_CASE("NonCopyable", "[Core][NonCopyable]")
{
    SECTION("Default constructable")
    {
        A class_a;
        PHI_UNUSED_PARAMETER(class_a);
    }

    SECTION("Move constructable")
    {
        A class_a;

        A class_b(phi::move(class_a));
        PHI_UNUSED_PARAMETER(class_b);
    }

    SECTION("Move assignable")
    {
        A class_a;

        A class_b = phi::move(class_a);
        PHI_UNUSED_PARAMETER(class_b);
    }
}
