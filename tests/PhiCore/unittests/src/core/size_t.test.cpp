#include <phi/test/test_macros.hpp>

#include <phi/core/size_t.hpp>
#include <phi/type_traits/is_integral.hpp>
#include <phi/type_traits/is_signed.hpp>
#include <phi/type_traits/is_unsigned.hpp>
#include <cstddef> // std::size_t
#include <type_traits>

TEST_CASE("size_t")
{
    CHECK_SAME_TYPE(phi::size_t, std::size_t);
    CHECK_SAME_TYPE(phi::size_t, decltype(sizeof(int)));
    CHECK_SAME_TYPE(phi::size_t, decltype(sizeof(long long)));
    CHECK_SAME_TYPE(phi::size_t, decltype(alignof(int)));
#if defined(__SIZE_TYPE__)
    CHECK_SAME_TYPE(phi::size_t, __SIZE_TYPE__);
#endif

    STATIC_REQUIRE(sizeof(phi::size_t) == sizeof(std::size_t));
    STATIC_REQUIRE(sizeof(phi::size_t) == sizeof(void*));
    STATIC_REQUIRE(phi::is_unsigned<phi::size_t>::value);
    STATIC_REQUIRE_FALSE(phi::is_signed<phi::size_t>::value);
    STATIC_REQUIRE(phi::is_integral<phi::size_t>::value);

    STATIC_REQUIRE(std::is_unsigned<phi::size_t>::value);
    STATIC_REQUIRE_FALSE(std::is_signed<phi::size_t>::value);
    STATIC_REQUIRE(std::is_integral<phi::size_t>::value);
}
