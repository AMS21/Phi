#include <phi/test/test_macros.hpp>

#include <phi/compiler_support/warning.hpp>
#include <phi/core/scoped_value_guard.hpp>

PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Wuseless-cast")

TEST_CASE("scoped_value_guard", "[Core][scoped_value_guard]")
{
    // ScopeValueGuard
    SECTION("default")
    {
        int i = 0;
        CHECK(i == 0);
        {
            phi::scoped_value_guard<int> guard(i);
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
            phi::scoped_value_guard<int> guard(i);

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
            const phi::scoped_value_guard<int> guard(i);

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
            phi::scoped_value_guard<int> guard(i);

            i = 21;
            guard.override_saved_value(99);
            CHECK(i == 21);
        }
        CHECK(i == 99);
    }

    // make_scope_value_guard
    SECTION("default")
    {
        int i = 0;
        CHECK(i == 0);
        {
            phi::scoped_value_guard<int> guard = phi::make_scoped_value_guard<int>(i);
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
            phi::scoped_value_guard<int> guard = phi::make_scoped_value_guard<int>(i);

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
            phi::scoped_value_guard<int> guard = phi::make_scoped_value_guard<int>(i);

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
            phi::scoped_value_guard<int> guard = phi::make_scoped_value_guard<int>(i);

            i = 21;
            guard.override_saved_value(99);
            CHECK(i == 21);
        }
        CHECK(i == 99);
    }

    // armed_scoped_value_guard
    SECTION("Default")
    {
        int i = 0;
        CHECK(i == 0);
        {
            phi::armed_scoped_value_guard<int> guard(i);

            i = 21;

            CHECK(guard.is_armed());
            CHECK(i == 21);
        }
        CHECK(i == 0);
    }

    SECTION("disarm")
    {
        int i = 0;
        CHECK(i == 0);
        {
            phi::armed_scoped_value_guard<int> guard(i);

            i = 21;

            CHECK(guard.is_armed());
            guard.disarm();
            CHECK_FALSE(guard.is_armed());

            CHECK(i == 21);
        }
        CHECK(i == 21);
    }

    SECTION("rearm already armed")
    {
        int i = 0;
        CHECK(i == 0);
        {
            phi::armed_scoped_value_guard<int> guard(i);

            i = 21;
            guard.rearm();

            CHECK(guard.is_armed());
            CHECK(i == 21);
        }
        CHECK(i == 0);
    }

    SECTION("rearm after disarm")
    {
        int i = 0;
        CHECK(i == 0);
        {
            phi::armed_scoped_value_guard<int> guard(i);

            guard.disarm();
            i = 21;
            guard.rearm();

            CHECK(guard.is_armed());
            CHECK(i == 21);
        }
        CHECK(i == 0);
    }

    // make_armed_scoped_value_guard
    SECTION("Default")
    {
        int i = 0;
        CHECK(i == 0);
        {
            phi::armed_scoped_value_guard<int> guard = phi::make_armed_scoped_value_guard<int>(i);

            i = 21;

            CHECK(guard.is_armed());
            CHECK(i == 21);
        }
        CHECK(i == 0);
    }

    SECTION("disarm")
    {
        int i = 0;
        CHECK(i == 0);
        {
            phi::armed_scoped_value_guard<int> guard = phi::make_armed_scoped_value_guard<int>(i);

            CHECK(guard.is_armed());
            guard.disarm();
            CHECK_FALSE(guard.is_armed());

            i = 21;
            CHECK(i == 21);
        }
        CHECK(i == 21);
    }

    SECTION("rearm already armed")
    {
        int i = 0;
        CHECK(i == 0);
        {
            phi::armed_scoped_value_guard<int> guard = phi::make_armed_scoped_value_guard<int>(i);

            i = 21;
            guard.rearm();

            CHECK(guard.is_armed());
            CHECK(i == 21);
        }
        CHECK(i == 0);
    }

    SECTION("rearm after disarm")
    {
        int i = 0;
        CHECK(i == 0);
        {
            phi::armed_scoped_value_guard<int> guard = phi::make_armed_scoped_value_guard<int>(i);

            guard.disarm();
            i = 21;
            guard.rearm();

            CHECK(guard.is_armed());
            CHECK(i == 21);
        }
        CHECK(i == 0);
    }
}

PHI_GCC_SUPPRESS_WARNING_POP()
