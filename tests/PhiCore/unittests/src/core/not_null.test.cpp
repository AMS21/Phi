#include <phi/test/test_macros.hpp>

#include <phi/core/not_null.hpp>
#include <memory>

TEST_CASE("NotNull", "[Core][NotNull]")
{
    SECTION("NotNull(T)")
    {
        int  integer = 3;
        int* pointer = &integer;

        phi::not_null<int*> not_null(&integer);
        phi::not_null<int*> not_null_ptr(pointer);

        CHECK(not_null.get() == &integer);
        CHECK(not_null.get() == pointer);
        CHECK(not_null_ptr.get() == &integer);
        CHECK(not_null_ptr.get() == pointer);
    }
}
