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
        int value = 0;
        CHECK(value == 0);
        {
            phi::scoped_value_guard<int> guard(value);
            CHECK(guard.get_saved_value() == 0);

            value = 21;

            CHECK(value == 21);
        }
        CHECK(value == 0);
    }

    SECTION("get_variable")
    {
        int value = 0;
        CHECK(value == 0);
        {
            phi::scoped_value_guard<int> guard(value);

            guard.get_variable() = 21;

            CHECK(value == 21);
        }
        CHECK(value == 0);
    }

    SECTION("get_variable const")
    {
        int value = 0;
        CHECK(value == 0);
        {
            const phi::scoped_value_guard<int> guard(value);

            value = 21;

            CHECK(guard.get_variable() == 21);
        }
        CHECK(value == 0);
    }

    SECTION("override_saved_value")
    {
        int value = 0;
        CHECK(value == 0);
        {
            phi::scoped_value_guard<int> guard(value);

            value = 21;
            guard.override_saved_value(99);
            CHECK(value == 21);
        }
        CHECK(value == 99);
    }

    // make_scope_value_guard
    SECTION("default")
    {
        int value = 0;
        CHECK(value == 0);
        {
            phi::scoped_value_guard<int> guard = phi::make_scoped_value_guard<int>(value);
            CHECK(guard.get_saved_value() == 0);

            value = 21;

            CHECK(value == 21);
        }
        CHECK(value == 0);
    }

    SECTION("get_variable")
    {
        int value = 0;
        CHECK(value == 0);
        {
            phi::scoped_value_guard<int> guard = phi::make_scoped_value_guard<int>(value);

            guard.get_variable() = 21;

            CHECK(value == 21);
        }
        CHECK(value == 0);
    }

    SECTION("get_variable const")
    {
        int value = 0;
        CHECK(value == 0);
        {
            phi::scoped_value_guard<int> guard = phi::make_scoped_value_guard<int>(value);

            value = 21;

            CHECK(guard.get_variable() == 21);
        }
        CHECK(value == 0);
    }

    SECTION("override_saved_value")
    {
        int value = 0;
        CHECK(value == 0);
        {
            phi::scoped_value_guard<int> guard = phi::make_scoped_value_guard<int>(value);

            value = 21;
            guard.override_saved_value(99);
            CHECK(value == 21);
        }
        CHECK(value == 99);
    }

    // armed_scoped_value_guard
    SECTION("Default")
    {
        int value = 0;
        CHECK(value == 0);
        {
            phi::armed_scoped_value_guard<int> guard(value);

            value = 21;

            CHECK(guard.is_armed());
            CHECK(value == 21);
        }
        CHECK(value == 0);
    }

    SECTION("get_variable")
    {
        int value = 0;
        CHECK(value == 0);
        {
            phi::armed_scoped_value_guard<int> guard(value);

            guard.get_variable() = 21;

            CHECK(value == 21);
        }
        CHECK(value == 0);
    }

    SECTION("get_variable const")
    {
        int value = 0;
        CHECK(value == 0);
        {
            const phi::armed_scoped_value_guard<int> guard(value);

            value = 21;

            CHECK(guard.get_variable() == 21);
        }
        CHECK(value == 0);
    }

    SECTION("override_saved_value")
    {
        int value = 0;
        CHECK(value == 0);
        {
            phi::armed_scoped_value_guard<int> guard(value);

            value = 21;
            guard.override_saved_value(99);
            CHECK(value == 21);
        }
        CHECK(value == 99);
    }

    SECTION("disarm")
    {
        int value = 0;
        CHECK(value == 0);
        {
            phi::armed_scoped_value_guard<int> guard(value);

            value = 21;

            CHECK(guard.is_armed());
            guard.disarm();
            CHECK_FALSE(guard.is_armed());

            CHECK(value == 21);
        }
        CHECK(value == 21);
    }

    SECTION("rearm already armed")
    {
        int value = 0;
        CHECK(value == 0);
        {
            phi::armed_scoped_value_guard<int> guard(value);

            value = 21;
            guard.rearm();

            CHECK(guard.is_armed());
            CHECK(value == 21);
        }
        CHECK(value == 0);
    }

    SECTION("rearm after disarm")
    {
        int value = 0;
        CHECK(value == 0);
        {
            phi::armed_scoped_value_guard<int> guard(value);

            guard.disarm();
            value = 21;
            guard.rearm();

            CHECK(guard.is_armed());
            CHECK(value == 21);
        }
        CHECK(value == 0);
    }

    // make_armed_scoped_value_guard
    SECTION("Default")
    {
        int value = 0;
        CHECK(value == 0);
        {
            phi::armed_scoped_value_guard<int> guard =
                    phi::make_armed_scoped_value_guard<int>(value);

            value = 21;

            CHECK(guard.is_armed());
            CHECK(value == 21);
        }
        CHECK(value == 0);
    }

    SECTION("get_variable")
    {
        int value = 0;
        CHECK(value == 0);
        {
            phi::armed_scoped_value_guard<int> guard =
                    phi::make_armed_scoped_value_guard<int>(value);

            guard.get_variable() = 21;

            CHECK(value == 21);
        }
        CHECK(value == 0);
    }

    SECTION("get_variable const")
    {
        int value = 0;
        CHECK(value == 0);
        {
            phi::armed_scoped_value_guard<int> guard =
                    phi::make_armed_scoped_value_guard<int>(value);

            value = 21;

            CHECK(guard.get_variable() == 21);
        }
        CHECK(value == 0);
    }

    SECTION("override_saved_value")
    {
        int value = 0;
        CHECK(value == 0);
        {
            phi::armed_scoped_value_guard<int> guard =
                    phi::make_armed_scoped_value_guard<int>(value);

            value = 21;
            guard.override_saved_value(99);
            CHECK(value == 21);
        }
        CHECK(value == 99);
    }

    SECTION("disarm")
    {
        int value = 0;
        CHECK(value == 0);
        {
            phi::armed_scoped_value_guard<int> guard =
                    phi::make_armed_scoped_value_guard<int>(value);

            CHECK(guard.is_armed());
            guard.disarm();
            CHECK_FALSE(guard.is_armed());

            value = 21;
            CHECK(value == 21);
        }
        CHECK(value == 21);
    }

    SECTION("rearm already armed")
    {
        int value = 0;
        CHECK(value == 0);
        {
            phi::armed_scoped_value_guard<int> guard =
                    phi::make_armed_scoped_value_guard<int>(value);

            value = 21;
            guard.rearm();

            CHECK(guard.is_armed());
            CHECK(value == 21);
        }
        CHECK(value == 0);
    }

    SECTION("rearm after disarm")
    {
        int value = 0;
        CHECK(value == 0);
        {
            phi::armed_scoped_value_guard<int> guard =
                    phi::make_armed_scoped_value_guard<int>(value);

            guard.disarm();
            value = 21;
            guard.rearm();

            CHECK(guard.is_armed());
            CHECK(value == 21);
        }
        CHECK(value == 0);
    }
}

PHI_GCC_SUPPRESS_WARNING_POP()
