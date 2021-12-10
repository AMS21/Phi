#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/algorithm/string_equals.hpp>
#include <phi/core/source_location.hpp>
#include <phi/type_traits/is_nothrow_default_constructible.hpp>
#include <phi/type_traits/is_nothrow_destructible.hpp>
#include <phi/type_traits/is_nothrow_move_assignable.hpp>
#include <phi/type_traits/is_nothrow_move_constructible.hpp>
#include <phi/type_traits/is_nothrow_swappable.hpp>
#include <phi/type_traits/is_trivially_copy_assignable.hpp>
#include <phi/type_traits/is_trivially_copy_constructible.hpp>
#include <phi/type_traits/is_trivially_destructible.hpp>
#include <phi/type_traits/is_trivially_move_assignable.hpp>
#include <phi/type_traits/is_trivially_move_constructible.hpp>

#if PHI_HAS_INTRINSIC_BUILTIN_FILE() && PHI_HAS_INTRINSIC_BUILTIN_FUNCTION() &&                    \
        PHI_HAS_INTRINSIC_BUILTIN_LINE()
#    define TEST_CURRENT() phi::source_location::current()
#else
#    define TEST_CURRENT() PHI_SOURCE_LOCATION_CURRENT()
#endif

TEST_CASE("source_location")
{
    SECTION("traits")
    {
        STATIC_REQUIRE(phi::is_nothrow_default_constructible<phi::source_location>::value);
        STATIC_REQUIRE(phi::is_nothrow_move_assignable<phi::source_location>::value);
        STATIC_REQUIRE(phi::is_nothrow_move_constructible<phi::source_location>::value);
        STATIC_REQUIRE(phi::is_nothrow_swappable<phi::source_location>::value);
        STATIC_REQUIRE(phi::is_nothrow_destructible<phi::source_location>::value);

        // trivial
        STATIC_REQUIRE(phi::is_trivially_copy_assignable<phi::source_location>::value);
        STATIC_REQUIRE(phi::is_trivially_copy_constructible<phi::source_location>::value);
        STATIC_REQUIRE(phi::is_trivially_move_assignable<phi::source_location>::value);
        STATIC_REQUIRE(phi::is_trivially_move_constructible<phi::source_location>::value);
        STATIC_REQUIRE(phi::is_trivially_destructible<phi::source_location>::value);

        CHECK_SAME_TYPE(phi::source_location::this_type, phi::source_location);
    }

    SECTION("default constructor")
    {
        phi::source_location loc;

        CHECK(phi::string_equals(loc.file_name(), ""));
        CHECK(loc.file_name_view().is_empty());
        CHECK(phi::string_equals(loc.function_name(), ""));
        CHECK(loc.function_name_view().is_empty());
        CHECK(loc.line() == 0);
        CHECK(loc.column() == 0);
    }

    SECTION("explicit constructor")
    {
        phi::source_location loc("my_file.cpp", "test_function", 42, 21);

        CHECK(phi::string_equals(loc.file_name(), "my_file.cpp"));
        CHECK(loc.file_name_view() == "my_file.cpp");
        CHECK(phi::string_equals(loc.function_name(), "test_function"));
        CHECK(loc.function_name_view() == "test_function");
        CHECK(loc.line() == 42);
        CHECK(loc.column() == 21);
    }

#if PHI_HAS_INTRINSIC_BUILTIN_FILE() && PHI_HAS_INTRINSIC_BUILTIN_FUNCTION() &&                    \
        PHI_HAS_INTRINSIC_BUILTIN_LINE()
    SECTION("current")
    {
        phi::source_location loc = phi::source_location::current();

        //CHECK(phi::string_equals(loc.file_name(), "source_location.test.cpp"));
        //CHECK(phi::string_equals(loc.function_name(), "phi_test_function"));
        CHECK(loc.line() == __LINE__ - 4);
#    if PHI_HAS_INTRINSIC_BUILTIN_COLUMN()
        CHECK(loc.column() == 36);
#    else
        CHECK(loc.column() == 0);
#    endif
    }
#endif

    SECTION("noexcept")
    {
        CHECK_NOEXCEPT(phi::source_location());
        CHECK_NOEXCEPT(phi::source_location("file.cpp", "function", 3, 1));
        CHECK_NOEXCEPT(phi::source_location::current());
        CHECK_NOEXCEPT(phi::source_location().line());
        CHECK_NOEXCEPT(phi::source_location().column());
        CHECK_NOEXCEPT(phi::source_location().file_name());
        CHECK_NOEXCEPT(phi::source_location().file_name_view());
        CHECK_NOEXCEPT(phi::source_location().function_name());
        CHECK_NOEXCEPT(phi::source_location().function_name_view());
    }

    SECTION("Constexpr")
    {
        constexpr phi::source_location l = phi::source_location("file.cpp", "function", 3, 1);

        STATIC_REQUIRE(phi::string_equals(l.file_name(), "file.cpp"));
        //STATIC_REQUIRE(l.file_name_view() == "file.cpp");
        STATIC_REQUIRE(phi::string_equals(l.function_name(), "function"));
        //STATIC_REQUIRE(l.function_name_view() == "function");
        STATIC_REQUIRE(l.line() == 3);
        STATIC_REQUIRE(l.column() == 1);
    }

    SECTION("PHI_SOURCE_LOCATION_CURRENT")
    {
        phi::source_location loc = PHI_SOURCE_LOCATION_CURRENT();

        //CHECK(phi::string_equals(loc.file_name(), "source_location.test.cpp"));
        //CHECK(phi::string_equals(loc.function_name(), "phi_test_function"));
        CHECK(loc.line() == __LINE__ - 4);
#if PHI_HAS_INTRINSIC_BUILTIN_COLUMN()
        CHECK(loc.column() == 64);
#else
        CHECK(loc.column() == 0);
#endif
    }
}

phi::source_location f()
{
    return TEST_CURRENT();
}

TEST_CASE("test f")
{
    phi::source_location f_loc = f();

    //CHECK(phi::string_equals(f_loc.file_name(), "source_location.test.cpp"));
    CHECK(phi::string_equals(f_loc.function_name(), "f"));
    CHECK(f_loc.line() == __LINE__ - 9);
#if PHI_HAS_INTRINSIC_BUILTIN_COLUMN()
    CHECK(f_loc.column() == 25);
#else
    CHECK(f_loc.column() == 0);
#endif
}

phi::source_location g()
{
#line 1000
    return TEST_CURRENT();
}

TEST_CASE("test g")
{
    phi::source_location g_loc = g();

    //CHECK(phi::string_equals(g_loc.file_name(), "source_location.test.cpp"));
    CHECK(phi::string_equals(g_loc.function_name(), "g"));
    CHECK(g_loc.function_name_view() == "g");
    CHECK(g_loc.line() == 1000);
#if PHI_HAS_INTRINSIC_BUILTIN_COLUMN()
    CHECK(g_loc.column() == 25);
#else
    CHECK(g_loc.column() == 0);
#endif
}

phi::source_location h()
{
#line 1000 "test_file.cpp"
    return TEST_CURRENT();
}

TEST_CASE("test h")
{
    phi::source_location h_loc = h();

    CHECK(phi::string_equals(h_loc.file_name(), "test_file.cpp"));
    CHECK(h_loc.file_name_view() == "test_file.cpp");
    CHECK(phi::string_equals(h_loc.function_name(), "h"));
    CHECK(h_loc.function_name_view() == "h");
    CHECK(h_loc.line() == 1000);
#if PHI_HAS_INTRINSIC_BUILTIN_COLUMN()
    CHECK(h_loc.column() == 25);
#else
    CHECK(h_loc.column() == 0);
#endif
}
