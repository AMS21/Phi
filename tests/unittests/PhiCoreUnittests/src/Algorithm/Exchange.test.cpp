#include <catch2/catch.hpp>

#include "TestTypes.hpp"
#include <Phi/Algorithm/Exchange.hpp>
#include <Phi/CompilerSupport/Constexpr.hpp>
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
        Tracked a{0};
        Tracked b{1};
        CHECK(phi::exchange(a, b).value() == 0);
    }

    {
        TrapConstructible a;
        TrapConstructible b;

        phi::exchange(a, b);
    }

    {
        TrapImplicitConversion a;
        TrapImplicitConversion b;

        phi::exchange(a, b);
    }

    {
        TrapComma a;
        TrapComma b;

        phi::exchange(a, b);
    }

    {
        TrapCall a;
        TrapCall b;

        phi::exchange(a, b);
    }

#if PHI_HAS_FEATURE_EXTENDED_CONSTEXPR()
    STATIC_REQUIRE(test_constexpr());
#endif
}
