#include <catch2/catch.hpp>

#include <Phi/Config/CPlusPlus.hpp>
#include <Phi/Core/ScopeGuard.hpp>
#include <functional>

void increment(int& val)
{
    val += 1;
}

static int global_value = 0;

void set_global_to_zero()
{
    global_value = 0;
}

#if PHI_CPP_STANDARD_IS_ATLEAST(17)
TEST_CASE("ScopeGuard lambda", "[Core][ScopeGuard]")
{
    int i = 3;
    CHECK(i == 3);
    {
        phi::ScopeGuard guard([&i]() { i = 7; });
        CHECK(i == 3);
    }
    CHECK(i == 7);
}

TEST_CASE("ScopeGuard const lvalue lambda", "[Core][ScopeGuard]")
{
    int i = 0;
    CHECK(i == 0);
    {
        const auto      const_lvalue_lambda = [&i]() { increment(i); };
        phi::ScopeGuard guard(const_lvalue_lambda);
        CHECK(i == 0);
    }
    CHECK(i == 1);
}

TEST_CASE("ScopeGuard mutable lvalue lambda", "[Core][ScopeGuard]")
{
    int i = 0;
    CHECK(i == 0);
    {
        auto            mutable_lvalue_lambda = [&i]() { increment(i); };
        phi::ScopeGuard guard(mutable_lvalue_lambda);
        CHECK(i == 0);
    }
    CHECK(i == 1);
}

TEST_CASE("ScopeGuard bind", "[Core][ScopeGuard]")
{
    int i = 0;
    CHECK(i == 0);
    {
        phi::ScopeGuard guard(std::bind(&increment, std::ref(i)));
        CHECK(i == 0);
    }
    CHECK(i == 1);
}

TEST_CASE("ScopeGuard function pointer", "[Core][ScopeGuard]")
{
    global_value = 42;
    CHECK(global_value == 42);
    {
        phi::ScopeGuard guard(&set_global_to_zero);
        CHECK(global_value == 42);
    }
    CHECK(global_value == 0);
}
#endif

TEST_CASE("make_scope_guard lambda", "[Core][ScopeGuard][make_scope_guard]")
{
    int i = 3;
    CHECK(i == 3);
    {
        auto guard = phi::make_scope_guard([&i]() { i = 7; });
        CHECK(i == 3);
    }
    CHECK(i == 7);
}

TEST_CASE("make_scope_guard const lvalue lambda", "[Core][ScopeGuard][make_scope_guard]")
{
    int i = 0;
    CHECK(i == 0);
    {
        const auto const_lvalue_lambda = [&i]() { increment(i); };
        auto       guard               = phi::make_scope_guard(const_lvalue_lambda);
        CHECK(i == 0);
    }
    CHECK(i == 1);
}

TEST_CASE("make_scope_guard mutable lvalue lambda", "[Core][ScopeGuard][make_scope_guard]")
{
    int i = 0;
    CHECK(i == 0);
    {
        auto mutable_lvalue_lambda = [&i]() { increment(i); };
        auto guard                 = phi::make_scope_guard(mutable_lvalue_lambda);
        CHECK(i == 0);
    }
    CHECK(i == 1);
}

TEST_CASE("make_scope_guard bind", "[Core][ScopeGuard][make_scope_guard]")
{
    int i = 0;
    CHECK(i == 0);
    {
        auto guard = phi::make_scope_guard(std::bind(&increment, std::ref(i)));
        CHECK(i == 0);
    }
    CHECK(i == 1);
}

TEST_CASE("make_scope_guard function pointer", "[Core][ScopeGuard][make_scope_guard]")
{
    global_value = 42;
    CHECK(global_value == 42);
    {
        auto guard = phi::make_scope_guard(&set_global_to_zero);
        CHECK(global_value == 42);
    }
    CHECK(global_value == 0);
}

/* ArmedScopeGuard */

#if PHI_CPP_STANDARD_IS_ATLEAST(17)
TEST_CASE("ArmedScopeGuard default", "[Core][ArmedScopeGuard]")
{
    int i = 0;
    CHECK(i == 0);
    {
        phi::ArmedScopeGuard guard([&i] { i = 17; });

        CHECK(guard.is_armed());
        CHECK(i == 0);
    }
    CHECK(i == 17);
}

TEST_CASE("ArmedScopeGuard disarm", "[Core][ArmedScopeGuard]")
{
    int i = 0;
    CHECK(i == 0);
    {
        phi::ArmedScopeGuard guard([&i] { i = 21; });

        CHECK(guard.is_armed());
        guard.disarm();
        CHECK_FALSE(guard.is_armed());

        CHECK(i == 0);
    }
    CHECK(i == 0);
}

TEST_CASE("ArmedScopeGuard rearm", "[Core][ArmedScopeGuard]")
{
    int i = 0;
    CHECK(i == 0);
    {
        phi::ArmedScopeGuard guard([&i] { i = 21; });

        guard.rearm();

        CHECK(guard.is_armed());
        CHECK(i == 0);
    }
    CHECK(i == 21);

    i = 0;
    {
        phi::ArmedScopeGuard guard([&i] { i = 21; });

        guard.disarm();
        guard.rearm();

        CHECK(guard.is_armed());
        CHECK(i == 0);
    }
    CHECK(i == 21);
}
#endif

TEST_CASE("make_armed_scope_guard default", "[Core][ArmedScopeGuard][make_armed_scope_guard]")
{
    int i = 0;
    CHECK(i == 0);
    {
        auto guard = phi::make_armed_scope_guard([&i] { i = 17; });

        CHECK(guard.is_armed());
        CHECK(i == 0);
    }
    CHECK(i == 17);
}

TEST_CASE("make_armed_scope_guard disarm", "[Core][ArmedScopeGuard][make_armed_scope_guard]")
{
    int i = 0;
    CHECK(i == 0);
    {
        auto guard = phi::make_armed_scope_guard([&i] { i = 21; });

        CHECK(guard.is_armed());
        guard.disarm();
        CHECK_FALSE(guard.is_armed());

        CHECK(i == 0);
    }
    CHECK(i == 0);
}

TEST_CASE("make_armed_scope_guard rearm", "[Core][ArmedScopeGuard][make_armed_scope_guard]")
{
    int i = 0;
    CHECK(i == 0);
    {
        auto guard = phi::make_armed_scope_guard([&i] { i = 21; });

        guard.rearm();

        CHECK(guard.is_armed());
        CHECK(i == 0);
    }
    CHECK(i == 21);

    i = 0;
    {
        auto guard = phi::make_armed_scope_guard([&i] { i = 21; });

        guard.disarm();
        guard.rearm();

        CHECK(guard.is_armed());
        CHECK(i == 0);
    }
    CHECK(i == 21);
}
