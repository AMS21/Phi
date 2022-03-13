#include <phi/test/test_macros.hpp>

#include <phi/compiler_support/compiler.hpp>
#include <phi/compiler_support/constexpr.hpp>
#include <phi/compiler_support/warning.hpp>
#include <phi/core/forward.hpp>
#include <phi/core/monitor.hpp>
#include <phi/core/size_t.hpp>
#include <thread>
#include <utility>
#include <vector>

PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Wuseless-cast")
PHI_GCC_SUPPRESS_WARNING("-Wnoexcept")

struct MonitorTestData
{
    constexpr MonitorTestData() noexcept
        : val(1u)
    {}

    constexpr MonitorTestData(int /*unused*/, double /*unused*/) noexcept
        : val(2u)
    {}

    phi::size_t val;
};

TEST_CASE("core.monitor.constructor")
{
    SECTION("monitor(ArgsT)")
    {
        phi::monitor<MonitorTestData> mon(3, 3.14);

        CHECK(mon->val == 2u);
    }

    SECTION("monitor(T)")
    {
        MonitorTestData               test_data;
        phi::monitor<MonitorTestData> mon(test_data);

        CHECK(mon->val == 1u);
    }
}

TEST_CASE("core.monitor.operators")
{
    SECTION("operator->")
    {
        phi::monitor<MonitorTestData> mon(3, 3.14);

        CHECK(mon->val == 2u);
    }

#if PHI_HAS_FEATURE_DECLTYPE_AUTO()
    SECTION("operator()")
    {
        phi::monitor<MonitorTestData> mon(3, 3.14);

        mon([](MonitorTestData& test_data) { test_data.val += 1u; });

        CHECK(mon->val == 3u);
    }
#endif
}

TEST_CASE("core.monitor.functions")
{
    SECTION("ManualLock")
    {
        phi::monitor<MonitorTestData> mon(3, 3.14);

        auto lock = mon.ManuallyLock();

        CHECK(lock->val == 2u);
        CHECK(lock.m_monitor == &mon);
    }

    SECTION("GetThreadUnsafeAccess")
    {
        phi::monitor<MonitorTestData> mon(3, 3.14);

        MonitorTestData& test_data = mon.GetThreadUnsafeAccess();

        test_data.val += 3u;

        CHECK(test_data.val == 5u);
        CHECK(mon->val == 5u);
    }
}

static PHI_CONSTEXPR_AND_CONST phi::size_t test_thread_count{20u};
static PHI_CONSTEXPR_AND_CONST phi::size_t test_write_count{10000u};

static void test_function(phi::monitor<MonitorTestData>& a) noexcept
{
    for (phi::size_t i{0u}; i < test_write_count; ++i)
    {
        a->val++;
    }
}

PHI_MSVC_SUPPRESS_WARNING_PUSH()
PHI_MSVC_SUPPRESS_WARNING(
        5039) // '_beginthreadex': pointer or reference to potentially throwing function passed to 'extern "C"' function under -EHc. Undefined behavior may occur if this function throws an exception.

TEST_CASE("core.monitor.thread_safety")
{
#if PHI_COMPILER_IS(EMCC)
    // Skip thread safety test in emscripten since the support for multiple threads is not very great,
    // See: https://emscripten.org/docs/porting/pthreads.html
    return;
#else
    phi::monitor<MonitorTestData> mon;

    std::vector<std::thread> threads;
    threads.reserve(test_thread_count);

    for (phi::size_t i{0u}; i < test_thread_count; ++i)
    {
        threads.emplace_back(test_function, std::ref(mon));
    }

    for (auto& thread : threads)
    {
        thread.join();
    }

    static PHI_CONSTEXPR_AND_CONST phi::size_t expected_value =
            1u + (test_thread_count * test_write_count);

    CHECK(mon->val == expected_value);
#endif
}

PHI_MSVC_SUPPRESS_WARNING_POP()
PHI_GCC_SUPPRESS_WARNING_POP()
