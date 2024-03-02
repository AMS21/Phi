#include <phi/test/test_macros.hpp>

#include <phi/compiler_support/platform.hpp>
#include <phi/core/wint_t.hpp>
#include <phi/type_traits/is_integral.hpp>
#include <phi/type_traits/is_signed.hpp>
#include <phi/type_traits/is_unsigned.hpp>
#include <cwctype> // std::wint_t (https://en.cppreference.com/w/cpp/header/cwctype)
#include <type_traits>

TEST_CASE("wint_t")
{
    CHECK_SAME_TYPE(phi::wint_t, std::wint_t);
    STATIC_REQUIRE(sizeof(phi::wint_t) == sizeof(std::wint_t));

    // Apple/Web Platform
#if PHI_PLATFORM_IS(APPLE) || PHI_PLATFORM_IS(WEB)

    CHECK_SAME_TYPE(phi::wint_t, int);
    STATIC_REQUIRE(sizeof(phi::wint_t) == sizeof(int));

    STATIC_REQUIRE_FALSE(phi::is_unsigned<phi::wint_t>::value);
    STATIC_REQUIRE(phi::is_signed<phi::wint_t>::value);

    STATIC_REQUIRE_FALSE(std::is_unsigned<phi::wint_t>::value);
    STATIC_REQUIRE(std::is_signed<phi::wint_t>::value);

// Windows platform
#elif PHI_PLATFORM_IS(WINDOWS)

    CHECK_SAME_TYPE(phi::wint_t, unsigned short);
    STATIC_REQUIRE(sizeof(phi::wint_t) == sizeof(unsigned short));

    STATIC_REQUIRE(phi::is_unsigned<phi::wint_t>::value);
    STATIC_REQUIRE_FALSE(phi::is_signed<phi::wint_t>::value);

    STATIC_REQUIRE(std::is_unsigned<phi::wint_t>::value);
    STATIC_REQUIRE_FALSE(std::is_signed<phi::wint_t>::value);

#else

    CHECK_SAME_TYPE(phi::wint_t, unsigned int);
    STATIC_REQUIRE(sizeof(phi::wint_t) == sizeof(unsigned int));

    STATIC_REQUIRE(phi::is_unsigned<phi::wint_t>::value);
    STATIC_REQUIRE_FALSE(phi::is_signed<phi::wint_t>::value);

    STATIC_REQUIRE(std::is_unsigned<phi::wint_t>::value);
    STATIC_REQUIRE_FALSE(std::is_signed<phi::wint_t>::value);

#endif

    STATIC_REQUIRE(phi::is_integral<phi::wint_t>::value);
    STATIC_REQUIRE(std::is_integral<phi::wint_t>::value);
}
