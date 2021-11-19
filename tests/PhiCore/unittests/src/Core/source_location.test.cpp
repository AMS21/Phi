#include <Phi/Test/TestMacros.hpp>

#include <Phi/Algorithm/StringEquals.hpp>
#include <Phi/Core/source_location.hpp>
#include <Phi/TypeTraits/is_nothrow_move_assignable.hpp>
#include <Phi/TypeTraits/is_nothrow_move_constructible.hpp>
#include <Phi/TypeTraits/is_nothrow_swappable.hpp>
#include <Phi/TypeTraits/is_trivially_copy_assignable.hpp>
#include <Phi/TypeTraits/is_trivially_copy_constructible.hpp>
#include <Phi/TypeTraits/is_trivially_move_assignable.hpp>
#include <Phi/TypeTraits/is_trivially_move_constructible.hpp>

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
        STATIC_REQUIRE(phi::is_nothrow_move_assignable<phi::source_location>::value);
        STATIC_REQUIRE(phi::is_nothrow_move_constructible<phi::source_location>::value);
        STATIC_REQUIRE(phi::is_nothrow_swappable<phi::source_location>::value);

        // trivial
        STATIC_REQUIRE(phi::is_trivially_copy_assignable<phi::source_location>::value);
        STATIC_REQUIRE(phi::is_trivially_copy_constructible<phi::source_location>::value);
        STATIC_REQUIRE(phi::is_trivially_move_assignable<phi::source_location>::value);
        STATIC_REQUIRE(phi::is_trivially_move_constructible<phi::source_location>::value);

        CHECK_SAME_TYPE(phi::source_location::this_type, phi::source_location);
    }

    SECTION("default constructor")
    {
        phi::source_location loc;

        CHECK(phi::StringEquals(loc.file_name(), ""));
        CHECK(phi::StringEquals(loc.function_name(), ""));
        CHECK(loc.line() == 0);
        CHECK(loc.column() == 0);
    }

    SECTION("explicit constructor")
    {
        phi::source_location loc("my_file.cpp", "test_function", 42, 21);

        CHECK(phi::StringEquals(loc.file_name(), "my_file.cpp"));
        CHECK(phi::StringEquals(loc.function_name(), "test_function"));
        CHECK(loc.line() == 42);
        CHECK(loc.column() == 21);
    }

#if PHI_HAS_INTRINSIC_BUILTIN_FILE() && PHI_HAS_INTRINSIC_BUILTIN_FUNCTION() &&                    \
        PHI_HAS_INTRINSIC_BUILTIN_LINE()
    SECTION("current")
    {
        phi::source_location loc = phi::source_location::current();

        //CHECK(phi::StringEquals(loc.file_name(), "source_location.test.cpp"));
        //CHECK(phi::StringEquals(loc.function_name(), "phi_test_function"));
        CHECK(loc.line() == __LINE__ - 4);
#    if PHI_HAS_INTRINSIC_BUILTIN_COLUMN()
        CHECK(loc.column() == 36);
#    else
        CHECK(loc.column() == 0);
#    endif
    }
#endif

    SECTION("PHI_SOURCE_LOCATION_CURRENT")
    {
        phi::source_location loc = PHI_SOURCE_LOCATION_CURRENT();

        //CHECK(phi::StringEquals(loc.file_name(), "source_location.test.cpp"));
        //CHECK(phi::StringEquals(loc.function_name(), "phi_test_function"));
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

    //CHECK(phi::StringEquals(f_loc.file_name(), "source_location.test.cpp"));
    CHECK(phi::StringEquals(f_loc.function_name(), "f"));
    CHECK(f_loc.line() == __LINE__ - 9);
#if PHI_HAS_INTRINSIC_BUILTIN_COLUMN()
    CHECK(f_loc.column() == 25);
#else
    CHECK(f_loc.column() == 0);
#endif
}

phi::source_location g()
{
#line 1
    return TEST_CURRENT();
}

TEST_CASE("test g")
{
    phi::source_location g_loc = g();

    //CHECK(phi::StringEquals(g_loc.file_name(), "source_location.test.cpp"));
    CHECK(phi::StringEquals(g_loc.function_name(), "g"));
    CHECK(g_loc.line() == 1);
#if PHI_HAS_INTRINSIC_BUILTIN_COLUMN()
    CHECK(g_loc.column() == 25);
#else
    CHECK(g_loc.column() == 0);
#endif
}

phi::source_location h()
{
#line 2 "test_file.cpp"
    return TEST_CURRENT();
}

TEST_CASE("test h")
{
    phi::source_location h_loc = h();

    CHECK(phi::StringEquals(h_loc.file_name(), "test_file.cpp"));
    CHECK(phi::StringEquals(h_loc.function_name(), "h"));
    CHECK(h_loc.line() == 2);
#if PHI_HAS_INTRINSIC_BUILTIN_COLUMN()
    CHECK(h_loc.column() == 25);
#else
    CHECK(h_loc.column() == 0);
#endif
}
