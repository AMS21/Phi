#include <catch2/catch_test_macros.hpp>

#include <Phi/Core/FinalAction.hpp>
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

TEST_CASE("FinalAction lambda", "[Core][FinalAction]")
{
    int i = 3;
    {
        phi::FinalAction action([&i]() { i = 7; });
        CHECK(i == 3);
    }
    CHECK(i == 7);
}

TEST_CASE("FinalAction const lvalue lambda", "[Core][FinalAction]")
{
    int i = 0;
    {
        const auto       const_lvalue_lambda = [&i]() { increment(i); };
        phi::FinalAction action(const_lvalue_lambda);
        CHECK(i == 0);
    }
    CHECK(i == 1);
}

TEST_CASE("FinalAction mutable lvalue lambda", "[Core][FinalAction]")
{
    int i = 0;
    {
        auto             mutable_lvalue_lambda = [&i]() { increment(i); };
        phi::FinalAction action(mutable_lvalue_lambda);
        CHECK(i == 0);
    }
    CHECK(i == 1);
}

TEST_CASE("FinalAction bind", "[Core][FinalAction]")
{
    int i = 0;
    {
        phi::FinalAction action(std::bind(&increment, std::ref(i)));
        CHECK(i == 0);
    }
    CHECK(i == 1);
}

TEST_CASE("FinalAction function pointer", "[Core][FinalAction]")
{
    global_value = 42;
    {
        phi::FinalAction action(&set_global_to_zero);
        CHECK(global_value == 42);
    }
    CHECK(global_value == 0);
}

TEST_CASE("finally lambda", "[Core][FinalAction][finally]")
{
    int i = 3;
    {
        auto action = phi::finally([&i]() { i = 7; });
        CHECK(i == 3);
    }
    CHECK(i == 7);
}

TEST_CASE("finally const lvalue lambda", "[Core][FinalAction][finally]")
{
    int i = 0;
    {
        const auto const_lvalue_lambda = [&i]() { increment(i); };
        auto action = phi::finally(const_lvalue_lambda);
        CHECK(i == 0);
    }
    CHECK(i == 1);
}

TEST_CASE("finally mutable lvalue lambda", "[Core][FinalAction][finally]")
{
    int i = 0;
    {
        auto mutable_lvalue_lambda = [&i]() { increment(i); };
        auto action = phi::finally(mutable_lvalue_lambda);
        CHECK(i == 0);
    }
    CHECK(i == 1);
}

TEST_CASE("finally bind", "[Core][FinalAction][finally]")
{
    int i = 0;
    {
        auto action = phi::finally(std::bind(&increment, std::ref(i)));
        CHECK(i == 0);
    }
    CHECK(i == 1);
}

TEST_CASE("finally function pointer", "[Core][FinalAction][finally]")
{
    global_value = 42;
    {
        auto action = phi::finally(&set_global_to_zero);
        CHECK(global_value == 42);
    }
    CHECK(global_value == 0);
}
