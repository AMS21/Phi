#include <phi/test/test_macros.hpp>

#include <phi/compiler_support/intrinsics/dynamic_object_size.hpp>

TEST_CASE("compiler_support.dynamic_object_size")
{
#if PHI_SUPPORTS_DYNAMIC_OBJECT_SIZE()

    int test = 0;
    REQUIRE(PHI_DYNAMIC_OBJECT_SIZE(&test, 0) == sizeof(int));

#else

    SKIP_CHECK();

#endif
}
