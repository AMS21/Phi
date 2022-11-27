#include <phi/test/test_macros.hpp>

#include <phi/core/max_align_t.hpp>
#include <phi/type_traits/is_pod.hpp>
#include <phi/type_traits/is_standard_layout.hpp>
#include <phi/type_traits/is_trivial.hpp>

PHI_EXTERNAL_HEADERS_BEGIN()
#include <cstddef> // std::max_align_t
PHI_EXTERNAL_HEADERS_END()

TEST_CASE("max_align_t")
{
#if PHI_HAS_WORKING_IS_TRIVIAL()
    STATIC_REQUIRE(phi::is_trivial<phi::max_align_t>::value);
#endif
#if PHI_HAS_WORKING_IS_STANDARD_LAYOUT()
    STATIC_REQUIRE(phi::is_standard_layout<phi::max_align_t>::value);
#endif
#if PHI_HAS_WORKING_IS_POD()
    STATIC_REQUIRE(phi::is_pod<phi::max_align_t>::value);
#endif

    STATIC_REQUIRE(alignof(phi::max_align_t) >= alignof(long long));
    STATIC_REQUIRE(alignof(phi::max_align_t) >= alignof(long double));
    STATIC_REQUIRE(alignof(phi::max_align_t) >= alignof(void*));

    // Standard compatibility
    STATIC_REQUIRE(alignof(phi::max_align_t) == alignof(std::max_align_t));
}
