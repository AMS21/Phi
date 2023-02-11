#include <phi/test/test_macros.hpp>

#include <phi/compiler_support/intrinsics/object_size.hpp>

TEST_CASE("compiler_support.object_size")
{
#if PHI_SUPPORTS_OBJECT_SIZE()

    int test = 0;
    REQUIRE(PHI_OBJECT_SIZE(&test, 0) == sizeof(int));

#else

    SKIP_CHECK();

#endif
}
