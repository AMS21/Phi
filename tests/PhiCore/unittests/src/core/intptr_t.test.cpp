#include <phi/test/test_macros.hpp>

#include <phi/core/intptr_t.hpp>
#include <phi/type_traits/is_integer.hpp>
#include <phi/type_traits/is_signed.hpp>
#include <phi/type_traits/is_unsigned.hpp>

PHI_EXTERNAL_HEADERS_BEGIN()
#include <cstdint>
PHI_EXTERNAL_HEADERS_END()

TEST_CASE("intptr_t")
{
    STATIC_REQUIRE(sizeof(phi::intptr_t) == sizeof(void*));
    STATIC_REQUIRE(sizeof(phi::intptr_t) == sizeof(int*));
    STATIC_REQUIRE(phi::is_signed<phi::intptr_t>::value);
    STATIC_REQUIRE_FALSE(phi::is_unsigned<phi::intptr_t>::value);
    STATIC_REQUIRE(phi::is_integer<phi::intptr_t>::value);

#if PHI_COMPILER_IS_NOT(EMCC)
    CHECK_SAME_TYPE(phi::intptr_t, std::intptr_t);
#endif
}

TEST_CASE("uintptr_t")
{
    STATIC_REQUIRE(sizeof(phi::uintptr_t) == sizeof(void*));
    STATIC_REQUIRE(sizeof(phi::uintptr_t) == sizeof(int*));
    STATIC_REQUIRE_FALSE(phi::is_signed<phi::uintptr_t>::value);
    STATIC_REQUIRE(phi::is_unsigned<phi::uintptr_t>::value);
    STATIC_REQUIRE(phi::is_integer<phi::uintptr_t>::value);

#if PHI_COMPILER_IS_NOT(EMCC)
    CHECK_SAME_TYPE(phi::uintptr_t, std::uintptr_t);
#endif
}
