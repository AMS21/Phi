#include <catch2/catch.hpp>

#include <Phi/Core/NotNull.hpp>
#include <memory>

TEST_CASE("NotNull", "[Core][NotNull]")
{
    SECTION("NotNull(T)")
    {
        int  i   = 3;
        int* ptr = &i;

        phi::NotNull<int*> not_null(&i);
        phi::NotNull<int*> not_null_ptr(ptr);

        CHECK(not_null.get() == &i);
        CHECK(not_null.get() == ptr);
        CHECK(not_null_ptr.get() == &i);
        CHECK(not_null_ptr.get() == ptr);
    }
}
