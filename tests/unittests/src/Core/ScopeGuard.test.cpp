#include <catch2/catch_test_macros.hpp>

#include <Phi/Core/ScopeGuard.hpp>
#include <functional>

void increment(int& val)
{
    val += 1;
}

int global_value = 0;

void set_global_to_zero()
{
    global_value = 0;
}

TEST_CASE("ScopeGuard lambda", "[Core][ScopeGuard]")
{
    int i = 3;
    {
        phi::ScopeGuard action([&i]() { i = 7; });
        CHECK(i == 3);
    }
    CHECK(i == 7);
}

TEST_CASE("ScopeGuard const lvalue lambda", "[Core][ScopeGuard]")
{
    int i = 0;
    {
        const auto      const_lvalue_lambda = [&i]() { increment(i); };
        phi::ScopeGuard action(const_lvalue_lambda);
        CHECK(i == 0);
    }
    CHECK(i == 1);
}

TEST_CASE("ScopeGuard mutable lvalue lambda", "[Core][ScopeGuard]")
{
    int i = 0;
    {
        auto            mutable_lvalue_lambda = [&i]() { increment(i); };
        phi::ScopeGuard action(mutable_lvalue_lambda);
        CHECK(i == 0);
    }
    CHECK(i == 1);
}

TEST_CASE("ScopeGuard bind", "[Core][ScopeGuard]")
{
    int i = 0;
    {
        phi::ScopeGuard action(std::bind(&increment, std::ref(i)));
        CHECK(i == 0);
    }
    CHECK(i == 1);
}

TEST_CASE("ScopeGuard function pointer", "[Core][ScopeGuard]")
{
    global_value = 42;
    {
        phi::ScopeGuard action(&set_global_to_zero);
        CHECK(global_value == 42);
    }
    CHECK(global_value == 0);
}

TEST_CASE("make_scope_guard lambda", "[Core][ScopeGuard][make_scope_guard]")
{
    int i = 3;
    {
        auto action = phi::make_scope_guard([&i]() { i = 7; });
        CHECK(i == 3);
    }
    CHECK(i == 7);
}

TEST_CASE("make_scope_guard const lvalue lambda", "[Core][ScopeGuard][make_scope_guard]")
{
    int i = 0;
    {
        const auto const_lvalue_lambda = [&i]() { increment(i); };
        auto       action              = phi::make_scope_guard(const_lvalue_lambda);
        CHECK(i == 0);
    }
    CHECK(i == 1);
}

TEST_CASE("make_scope_guard mutable lvalue lambda", "[Core][ScopeGuard][make_scope_guard]")
{
    int i = 0;
    {
        auto mutable_lvalue_lambda = [&i]() { increment(i); };
        auto action                = phi::make_scope_guard(mutable_lvalue_lambda);
        CHECK(i == 0);
    }
    CHECK(i == 1);
}

TEST_CASE("make_scope_guard bind", "[Core][ScopeGuard][make_scope_guard]")
{
    int i = 0;
    {
        auto action = phi::make_scope_guard(std::bind(&increment, std::ref(i)));
        CHECK(i == 0);
    }
    CHECK(i == 1);
}

TEST_CASE("make_scope_guard function pointer", "[Core][ScopeGuard][make_scope_guard]")
{
    global_value = 42;
    {
        auto action = phi::make_scope_guard(&set_global_to_zero);
        CHECK(global_value == 42);
    }
    CHECK(global_value == 0);
}
