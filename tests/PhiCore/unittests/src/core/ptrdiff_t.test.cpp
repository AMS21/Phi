#include <phi/test/test_macros.hpp>

#include <phi/compiler_support/cpp_standard.hpp>
#include <phi/core/ptrdiff_t.hpp>
#include <phi/type_traits/is_signed.hpp>
#include <phi/type_traits/is_unsafe_integral.hpp>
#include <climits> // CHAR_BIT
#include <cstddef>

TEST_CASE("ptrdiff_t")
{
    STATIC_REQUIRE(sizeof(phi::ptrdiff_t) == sizeof(void*));
    STATIC_REQUIRE(phi::is_signed<phi::ptrdiff_t>::value);
    STATIC_REQUIRE(phi::is_unsafe_integral<phi::ptrdiff_t>::value);
#if defined(__PTRDIFF_TYPE__)
    CHECK_SAME_TYPE(phi::ptrdiff_t, __PTRDIFF_TYPE__);
#endif

    // Since C++-11 'ptrdiff_t' is at least 16 bits
#if PHI_CPP_STANDARD_IS_ATLEAST(11)
    STATIC_REQUIRE(sizeof(phi::ptrdiff_t) * CHAR_BIT >= 16);
#endif

    // Standard compatibility
    CHECK_SAME_TYPE(phi::ptrdiff_t, std::ptrdiff_t);
}
