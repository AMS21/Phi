#include <catch2/catch_test_macros.hpp>

#include <Phi/Core/Monitor.hpp>
#include <thread>
#include <utility>
#include <vector>

struct A
{
    A()
        : val(1)
    {}

    A(int /*unused*/, double /*unused*/)
        : val(2)
    {}

    int val;
};

constexpr std::size_t test_thread_count{20};
constexpr std::size_t test_write_count{10000};

static void test_function(phi::Monitor<A>& a)
{
    for (std::size_t i = 0; i < test_write_count; ++i)
    {
        a->val++;
    }
}

TEST_CASE("Monitor", "[Core][Monitor]")
{
    SECTION("Monitor(ArgsT)")
    {
        phi::Monitor<A> mon(3, 3.14);

        CHECK(mon->val == 2);
    }

    SECTION("Monitor(T)")
    {
        A               a;
        phi::Monitor<A> mon(a);

        CHECK(mon->val == 1);
    }

    SECTION("operator->")
    {
        phi::Monitor<A> mon(3, 3.14);

        CHECK(mon->val == 2);
    }

    SECTION("operator()")
    {
        phi::Monitor<A> mon(3, 3.14);

        mon([](A& a) { a.val += 1; });

        CHECK(mon->val == 3);
    }

    SECTION("ManualLock")
    {
        phi::Monitor<A> mon(3, 3.14);

        auto lock = mon.ManuallyLock();

        CHECK(lock->val == 2);
        CHECK(lock.m_Monitor == &mon);
    }

    SECTION("GetThreadUnsafeAccess")
    {
        phi::Monitor<A> mon(3, 3.14);

        A& a = mon.GetThreadUnsafeAccess();

        a.val += 3;

        CHECK(a.val == 5);
        CHECK(mon->val == 5);
    }

    SECTION("Thread safety")
    {
        phi::Monitor<A> mon;

        std::vector<std::thread> threads;
        threads.reserve(test_thread_count);

        for (std::size_t i = 0; i < test_thread_count; ++i)
        {
            threads.emplace_back(test_function, std::ref(mon));
        }

        for (auto& thread : threads)
        {
            thread.join();
        }

        constexpr int expected_value = 1 + (test_thread_count * test_write_count);

        CHECK(mon->val == expected_value);
    }
}
