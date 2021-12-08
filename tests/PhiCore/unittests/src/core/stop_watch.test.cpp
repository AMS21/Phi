#include <phi/test/test_macros.hpp>

#include <phi/core/stop_watch.hpp>
#include <chrono>
#include <ratio>
#include <thread>

TEST_CASE("stop_watch", "[Core][stop_watch]")
{
    SECTION("defaulted")
    {
        phi::stop_watch<> sw;

        std::this_thread::sleep_for(std::chrono::milliseconds(2));

        std::chrono::duration<double, std::milli> elapsed = sw.get_elapsed();

        CHECK(elapsed.count() >= 1);
    }

    SECTION("system clock")
    {
        phi::stop_watch<std::chrono::system_clock> sw;

        std::this_thread::sleep_for(std::chrono::milliseconds(2));

        std::chrono::duration<double, std::milli> elapsed = sw.get_elapsed();

        CHECK(elapsed.count() >= 1);
    }

    SECTION("steady clock")
    {
        phi::stop_watch<std::chrono::steady_clock> sw;

        std::this_thread::sleep_for(std::chrono::milliseconds(2));

        std::chrono::duration<double, std::milli> elapsed = sw.get_elapsed();

        CHECK(elapsed.count() >= 1);
    }

    SECTION("Elapsed cast")
    {
        phi::stop_watch<std::chrono::system_clock> sw;

        std::this_thread::sleep_for(std::chrono::milliseconds(2));

        std::chrono::duration<std::int32_t, std::micro> elapsed =
                sw.get_elapsed<std::int32_t, std::micro>();

        CHECK(elapsed.count() >= 1000);
    }
}
