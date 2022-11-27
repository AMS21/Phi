#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/algorithm/exchange.hpp>
#include <phi/compiler_support/constexpr.hpp>

PHI_EXTERNAL_HEADERS_BEGIN()
#include <string>
PHI_EXTERNAL_HEADERS_END()

#if PHI_HAS_FEATURE_EXTENDED_CONSTEXPR()
PHI_EXTENDED_CONSTEXPR bool test_constexpr()
{
    int value = 12;

    if (12 != phi::exchange(value, 23) || value != 23)
    {
        return false;
    }

    if (23 != phi::exchange(value, static_cast<short>(67)) || value != 67)
    {
        return false;
    }

    if (67 != phi::exchange<int, short>(value, {}) || value != 0)
    {
        return false;
    }
    return true;
}
#endif

TEST_CASE("exchange")
{
    {
        int value = 12;
        CHECK(phi::exchange(value, 23) == 12);
        CHECK(value == 23);
        CHECK(phi::exchange(value, static_cast<short>(67)) == 23);
        CHECK(value == 67);

        CHECK((phi::exchange<int, short>(value, {})) == 67);
        CHECK(value == 0);
    }

    {
        bool boolean = false;
        CHECK_FALSE(phi::exchange(boolean, true));
        CHECK(boolean);
    }

    {
        const std::string string1("Hi Mom!");
        const std::string string2("Yo Dad!");
        std::string       string3 = string1; // Mom
        CHECK(phi::exchange(string3, string2) == string1);
        CHECK(string3 == string2);
        CHECK(phi::exchange(string3, "Hi Mom!") == string2);
        CHECK(string3 == string1);

        string3 = string2; // Dad
        CHECK(phi::exchange(string3, {}) == string2);
        CHECK(string3.empty());

        string3 = string2; // Dad
        CHECK(phi::exchange(string3, "") == string2);
        CHECK(string3.empty());
    }

    {
        tracked lhs{0};
        tracked rhs{1};
        CHECK(phi::exchange(lhs, rhs).value() == 0);
    }

    {
        trap_constructible lhs;
        trap_constructible rhs;

        phi::exchange(lhs, rhs);
    }

    {
        trap_implicit_conversion lhs;
        trap_implicit_conversion rhs;

        phi::exchange(lhs, rhs);
    }

    {
        trap_comma lhs;
        trap_comma rhs;

        phi::exchange(lhs, rhs);
    }

    {
        trap_call lhs;
        trap_call rhs;

        phi::exchange(lhs, rhs);
    }

#if PHI_HAS_FEATURE_EXTENDED_CONSTEXPR()
    STATIC_REQUIRE(test_constexpr());
#endif
}
