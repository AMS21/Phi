#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/algorithm/exchange.hpp>
#include <phi/compiler_support/constexpr.hpp>
#include <string>

#if PHI_HAS_FEATURE_EXTENDED_CONSTEXPR()
PHI_EXTENDED_CONSTEXPR bool test_constexpr()
{
    int v = 12;

    if (12 != phi::exchange(v, 23) || v != 23)
    {
        return false;
    }

    if (23 != phi::exchange(v, static_cast<short>(67)) || v != 67)
    {
        return false;
    }

    if (67 != phi::exchange<int, short>(v, {}) || v != 0)
    {
        return false;
    }
    return true;
}
#endif

TEST_CASE("exchange")
{
    {
        int v = 12;
        CHECK(phi::exchange(v, 23) == 12);
        CHECK(v == 23);
        CHECK(phi::exchange(v, static_cast<short>(67)) == 23);
        CHECK(v == 67);

        CHECK((phi::exchange<int, short>(v, {})) == 67);
        CHECK(v == 0);
    }

    {
        bool b = false;
        CHECK_FALSE(phi::exchange(b, true));
        CHECK(b);
    }

    {
        const std::string s1("Hi Mom!");
        const std::string s2("Yo Dad!");
        std::string       s3 = s1; // Mom
        CHECK(phi::exchange(s3, s2) == s1);
        CHECK(s3 == s2);
        CHECK(phi::exchange(s3, "Hi Mom!") == s2);
        CHECK(s3 == s1);

        s3 = s2; // Dad
        CHECK(phi::exchange(s3, {}) == s2);
        CHECK(s3.empty());

        s3 = s2; // Dad
        CHECK(phi::exchange(s3, "") == s2);
        CHECK(s3.empty());
    }

    {
        tracked a{0};
        tracked b{1};
        CHECK(phi::exchange(a, b).value() == 0);
    }

    {
        trap_constructible a;
        trap_constructible b;

        phi::exchange(a, b);
    }

    {
        trap_implicit_conversion a;
        trap_implicit_conversion b;

        phi::exchange(a, b);
    }

    {
        trap_comma a;
        trap_comma b;

        phi::exchange(a, b);
    }

    {
        trap_call a;
        trap_call b;

        phi::exchange(a, b);
    }

#if PHI_HAS_FEATURE_EXTENDED_CONSTEXPR()
    STATIC_REQUIRE(test_constexpr());
#endif
}
