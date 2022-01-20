#include <phi/test/test_macros.hpp>

#include <phi/compiler_support/compiler.hpp>
#include <phi/compiler_support/warning.hpp>
#include <phi/core/forward.hpp>
#include <phi/core/monitor.hpp>
#include <thread>
#include <utility>
#include <vector>

PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Wuseless-cast")

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

static void test_function(phi::monitor<A>& a)
{
    for (std::size_t i = 0; i < test_write_count; ++i)
    {
        a->val++;
    }
}

TEST_CASE("monitor", "[Core][monitor]")
{
    SECTION("monitor(ArgsT)")
    {
        phi::monitor<A> mon(3, 3.14);

        CHECK(mon->val == 2);
    }

    SECTION("monitor(T)")
    {
        A               a;
        phi::monitor<A> mon(a);

        CHECK(mon->val == 1);
    }

    SECTION("operator->")
    {
        phi::monitor<A> mon(3, 3.14);

        CHECK(mon->val == 2);
    }

#if PHI_HAS_FEATURE_DECLTYPE_AUTO()
    SECTION("operator()")
    {
        phi::monitor<A> mon(3, 3.14);

        mon([](A& a) { a.val += 1; });

        CHECK(mon->val == 3);
    }
#endif

    SECTION("ManualLock")
    {
        phi::monitor<A> mon(3, 3.14);

        auto lock = mon.ManuallyLock();

        CHECK(lock->val == 2);
        CHECK(lock.m_monitor == &mon);
    }

    SECTION("GetThreadUnsafeAccess")
    {
        phi::monitor<A> mon(3, 3.14);

        A& a = mon.GetThreadUnsafeAccess();

        a.val += 3;

        CHECK(a.val == 5);
        CHECK(mon->val == 5);
    }

    SECTION("Thread safety")
    {
#if PHI_COMPILER_IS(EMCC)
        // Skip thread safety test in emscripten since the support for multiple threads is not very great,
        // See: https://emscripten.org/docs/porting/pthreads.html
        return;
#else
        phi::monitor<A> mon;

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
#endif
    }
}

PHI_GCC_SUPPRESS_WARNING_POP()
