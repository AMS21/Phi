#include <phi/test/test_macros.hpp>

#include <phi/compiler_support/cpp_standard.hpp>
#include <phi/core/size_t.hpp>
#include <phi/core/ssize_t.hpp>
#include <phi/type_traits/is_integral.hpp>
#include <phi/type_traits/is_signed.hpp>
#include <phi/type_traits/is_unsigned.hpp>
#include <phi/type_traits/make_signed.hpp>
#include <climits> // CHAR_BIT
#include <cstddef> // std::size_t
#include <type_traits>

TEST_CASE("ssize_t")
{
    CHECK_SAME_TYPE(phi::ssize_t, phi::make_signed_t<phi::size_t>);
    CHECK_SAME_TYPE(phi::ssize_t, phi::make_signed_t<std::size_t>);
    CHECK_SAME_TYPE(phi::ssize_t, phi::make_signed_t<decltype(sizeof(int))>);
    CHECK_SAME_TYPE(phi::ssize_t, phi::make_signed_t<decltype(sizeof(long long))>);
    CHECK_SAME_TYPE(phi::ssize_t, phi::make_signed_t<decltype(alignof(int))>);

    STATIC_REQUIRE(sizeof(phi::ssize_t) == sizeof(phi::size_t));
    STATIC_REQUIRE(sizeof(phi::ssize_t) == sizeof(std::size_t));
    STATIC_REQUIRE(sizeof(phi::size_t) == sizeof(void*));
    // Since C++-11 'size_t' is at least 16 bits so 'ssize_t' should be as well
#if PHI_CPP_STANDARD_IS_ATLEAST(11)
    STATIC_REQUIRE(sizeof(phi::ssize_t) * CHAR_BIT >= 16);
#endif

    STATIC_REQUIRE_FALSE(phi::is_unsigned<phi::ssize_t>::value);
    STATIC_REQUIRE(phi::is_signed<phi::ssize_t>::value);
    STATIC_REQUIRE(phi::is_integral<phi::ssize_t>::value);

    STATIC_REQUIRE_FALSE(std::is_unsigned<phi::ssize_t>::value);
    STATIC_REQUIRE(std::is_signed<phi::ssize_t>::value);
    STATIC_REQUIRE(std::is_integral<phi::ssize_t>::value);
}
