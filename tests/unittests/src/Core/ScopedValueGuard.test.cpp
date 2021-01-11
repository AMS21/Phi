#include <catch2/catch_test_macros.hpp>

#include <Phi/Core/ScopedValueGuard.hpp>

TEST_CASE("ScopedValueGuard", "[Core][ScopedValueGuard]")
{
    SECTION("default")
    {
        int i = 0;
        CHECK(i == 0);
        {
            phi::ScopedValueGuard guard(i);
            CHECK(guard.get_saved_value() == 0);

            i = 21;

            CHECK(i == 21);
        }
        CHECK(i == 0);
    }

    SECTION("get_variable")
    {
        int i = 0;
        CHECK(i == 0);
        {
            phi::ScopedValueGuard guard(i);

            guard.get_variable() = 21;

            CHECK(i == 21);
        }
        CHECK(i == 0);
    }

    SECTION("get_variable const")
    {
        int i = 0;
        CHECK(i == 0);
        {
            const phi::ScopedValueGuard guard(i);

            i = 21;

            CHECK(guard.get_variable() == 21);
        }
        CHECK(i == 0);
    }

    SECTION("override_saved_value")
    {
        int i = 0;
        CHECK(i == 0);
        {
            phi::ScopedValueGuard guard(i);

            i = 21;
            guard.override_saved_value(99);
            CHECK(i == 21);
        }
        CHECK(i == 99);
    }
}

TEST_CASE("make_scoped_value_guard", "[Core][ScopedValueGuard][make_scoped_value_guard]")
{
    SECTION("default")
    {
        int i = 0;
        CHECK(i == 0);
        {
            auto guard = phi::make_scoped_value_guard(i);
            CHECK(guard.get_saved_value() == 0);

            i = 21;

            CHECK(i == 21);
        }
        CHECK(i == 0);
    }

    SECTION("get_variable")
    {
        int i = 0;
        CHECK(i == 0);
        {
            auto guard = phi::make_scoped_value_guard(i);

            guard.get_variable() = 21;

            CHECK(i == 21);
        }
        CHECK(i == 0);
    }

    SECTION("get_variable const")
    {
        int i = 0;
        CHECK(i == 0);
        {
            auto guard = phi::make_scoped_value_guard(i);

            i = 21;

            CHECK(guard.get_variable() == 21);
        }
        CHECK(i == 0);
    }

    SECTION("override_saved_value")
    {
        int i = 0;
        CHECK(i == 0);
        {
            auto guard = phi::make_scoped_value_guard(i);

            i = 21;
            guard.override_saved_value(99);
            CHECK(i == 21);
        }
        CHECK(i == 99);
    }
}

/* ArmedScopedValueGuard */

TEST_CASE("ArmedScopedValueGuard default", "[Core][ScopedValueGuard][ArmedScopedValueGuard]")
{
    SECTION("Default")
    {
        int i = 0;
        CHECK(i == 0);
        {
            phi::ArmedScopedValueGuard guard(i);

            i = 21;
            CHECK(i == 21);
        }
        CHECK(i == 0);
    }

    SECTION("disarm")
    {
        int i = 0;
        CHECK(i == 0);
        {
            phi::ArmedScopedValueGuard guard(i);

            i = 21;
            guard.disarm();
            CHECK(i == 21);
        }
        CHECK(i == 21);
    }

    SECTION("rearm already armed")
    {
        int i = 0;
        CHECK(i == 0);
        {
            phi::ArmedScopedValueGuard guard(i);

            i = 21;
            guard.rearm();
            CHECK(i == 21);
        }
        CHECK(i == 0);
    }

    SECTION("rearm after disarm")
    {
        int i = 0;
        CHECK(i == 0);
        {
            phi::ArmedScopedValueGuard guard(i);

            guard.disarm();
            i = 21;
            guard.rearm();
            CHECK(i == 21);
        }
        CHECK(i == 0);
    }
}

TEST_CASE("make_armed_scoped_value_guard default",
          "[Core][ScopedValueGuard][ArmedScopedValueGuard][make_armed_scoped_value_guard]")
{
    SECTION("Default")
    {
        int i = 0;
        CHECK(i == 0);
        {
            auto guard = phi::make_armed_scoped_value_guard(i);

            i = 21;
            CHECK(i == 21);
        }
        CHECK(i == 0);
    }

    SECTION("disarm")
    {
        int i = 0;
        CHECK(i == 0);
        {
            auto guard = phi::make_armed_scoped_value_guard(i);

            i = 21;
            guard.disarm();
            CHECK(i == 21);
        }
        CHECK(i == 21);
    }

    SECTION("rearm already armed")
    {
        int i = 0;
        CHECK(i == 0);
        {
            auto guard = phi::make_armed_scoped_value_guard(i);

            i = 21;
            guard.rearm();
            CHECK(i == 21);
        }
        CHECK(i == 0);
    }

    SECTION("rearm after disarm")
    {
        int i = 0;
        CHECK(i == 0);
        {
            auto guard = phi::make_armed_scoped_value_guard(i);

            guard.disarm();
            i = 21;
            guard.rearm();
            CHECK(i == 21);
        }
        CHECK(i == 0);
    }
}
