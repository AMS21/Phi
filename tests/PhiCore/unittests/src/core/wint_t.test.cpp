#include <phi/test/test_macros.hpp>

#include <phi/core/wint_t.hpp>
#include <phi/type_traits/is_integral.hpp>
#include <phi/type_traits/is_signed.hpp>
#include <phi/type_traits/is_unsigned.hpp>
#include <cwctype> // std::wint_t (https://en.cppreference.com/w/cpp/header/cwctype)
#include <type_traits>

TEST_CASE("wint_t")
{
    CHECK_SAME_TYPE(phi::wint_t, std::wint_t);
    CHECK_SAME_TYPE(phi::wint_t, unsigned int);

    STATIC_REQUIRE(sizeof(phi::wint_t) == sizeof(std::wint_t));
    STATIC_REQUIRE(sizeof(phi::wint_t) == sizeof(unsigned int));
    STATIC_REQUIRE(phi::is_unsigned<phi::wint_t>::value);
    STATIC_REQUIRE_FALSE(phi::is_signed<phi::wint_t>::value);
    STATIC_REQUIRE(phi::is_integral<phi::wint_t>::value);

    STATIC_REQUIRE(std::is_unsigned<phi::wint_t>::value);
    STATIC_REQUIRE_FALSE(std::is_signed<phi::wint_t>::value);
    STATIC_REQUIRE(std::is_integral<phi::wint_t>::value);
}
