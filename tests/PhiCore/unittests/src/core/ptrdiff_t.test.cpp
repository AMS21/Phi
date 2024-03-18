#include <phi/test/test_macros.hpp>

#include <phi/core/ptrdiff_t.hpp>
#include <phi/type_traits/is_signed.hpp>
#include <phi/type_traits/is_unsafe_integral.hpp>
#include <cstddef>

TEST_CASE("ptrdiff_t")
{
    STATIC_REQUIRE(sizeof(phi::ptrdiff_t) == sizeof(void*));
    STATIC_REQUIRE(phi::is_signed<phi::ptrdiff_t>::value);
    STATIC_REQUIRE(phi::is_unsafe_integral<phi::ptrdiff_t>::value);
#if defined(__PTRDIFF_TYPE__)
    CHECK_SAME_TYPE(phi::ptrdiff_t, __PTRDIFF_TYPE__);
#endif

    // Standard compatibility
    CHECK_SAME_TYPE(phi::ptrdiff_t, std::ptrdiff_t);
}
