#include <phi/test/test_macros.hpp>

#include <phi/core/stop_watch.hpp>

PHI_EXTERNAL_HEADERS_BEGIN()
#include <chrono>
#include <ratio>
#include <thread>
PHI_EXTERNAL_HEADERS_END()

TEST_CASE("stop_watch", "[Core][stop_watch]")
{
    SECTION("defaulted")
    {
        phi::stop_watch<> watch;

        std::this_thread::sleep_for(std::chrono::milliseconds(2));

        std::chrono::duration<double, std::milli> elapsed = watch.get_elapsed();

        CHECK(elapsed.count() >= 1);
    }

    SECTION("system clock")
    {
        phi::stop_watch<std::chrono::system_clock> watch;

        std::this_thread::sleep_for(std::chrono::milliseconds(2));

        std::chrono::duration<double, std::milli> elapsed = watch.get_elapsed();

        CHECK(elapsed.count() >= 1);
    }

    SECTION("steady clock")
    {
        phi::stop_watch<std::chrono::steady_clock> watch;

        std::this_thread::sleep_for(std::chrono::milliseconds(2));

        std::chrono::duration<double, std::milli> elapsed = watch.get_elapsed();

        CHECK(elapsed.count() >= 1);
    }

    SECTION("Elapsed cast")
    {
        phi::stop_watch<std::chrono::system_clock> watch;

        std::this_thread::sleep_for(std::chrono::milliseconds(2));

        std::chrono::duration<std::int32_t, std::micro> elapsed =
                watch.get_elapsed<std::int32_t, std::micro>();

        CHECK(elapsed.count() >= 1000);
    }
}
