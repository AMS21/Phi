#include <phi/test/test_macros.hpp>

#include <phi/compiler_support/char8_t.hpp>
#include <phi/compiler_support/warning.hpp>
#include <phi/type_traits/is_class.hpp>
#include <phi/type_traits/is_enum.hpp>
#include <phi/type_traits/is_trivial.hpp>
#include <phi/type_traits/is_unsafe_arithmetic.hpp>
#include <phi/type_traits/is_unsafe_fundamental.hpp>
#include <phi/type_traits/is_unsafe_integral.hpp>
#include <phi/type_traits/is_unsafe_signed.hpp>
#include <phi/type_traits/is_unsafe_unsigned.hpp>

PHI_MSVC_SUPPRESS_WARNING_PUSH()
PHI_MSVC_SUPPRESS_WARNING(4668) // '__STDC_WANT_SECURE_LIB__' is not defined as a preprocessor macro, replacing with '0' for '#if/#elif'

#include <climits>

PHI_MSVC_SUPPRESS_WARNING_POP()

TEST_CASE("Compiler support - char8_t")
{
    STATIC_REQUIRE(sizeof(char8_t) * CHAR_BIT == 8);

    // Type traits
    STATIC_REQUIRE(phi::is_unsafe_unsigned<char8_t>::value);
    STATIC_REQUIRE_FALSE(phi::is_unsafe_signed<char8_t>::value);
    STATIC_REQUIRE(phi::is_unsafe_integral<char8_t>::value);
#if PHI_HAS_WORKING_IS_ENUM()
    STATIC_REQUIRE_FALSE(phi::is_enum<char8_t>::value);
#endif
    STATIC_REQUIRE(phi::is_unsafe_fundamental<char8_t>::value);
    STATIC_REQUIRE(phi::is_unsafe_arithmetic<char8_t>::value);
#if PHI_HAS_WORKING_IS_TRIVIAL()
    STATIC_REQUIRE(phi::is_trivial<char8_t>::value);
#endif
#if PHI_HAS_WORKING_IS_CLASS()
    STATIC_REQUIRE_FALSE(phi::is_class<char8_t>::value);
#endif
}
