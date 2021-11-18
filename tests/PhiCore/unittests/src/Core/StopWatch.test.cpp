#include <Phi/Test/TestMacros.hpp>

#include <Phi/Core/StopWatch.hpp>
#include <chrono>
#include <ratio>
#include <thread>

TEST_CASE("StopWatch", "[Core][StopWatch]")
{
    SECTION("defaulted")
    {
        phi::StopWatch<> sw;

        std::this_thread::sleep_for(std::chrono::milliseconds(2));

        std::chrono::duration<double, std::milli> elapsed = sw.getElapsed();

        CHECK(elapsed.count() >= 1);
    }

    SECTION("system clock")
    {
        phi::StopWatch<std::chrono::system_clock> sw;

        std::this_thread::sleep_for(std::chrono::milliseconds(2));

        std::chrono::duration<double, std::milli> elapsed = sw.getElapsed();

        CHECK(elapsed.count() >= 1);
    }

    SECTION("steady clock")
    {
        phi::StopWatch<std::chrono::steady_clock> sw;

        std::this_thread::sleep_for(std::chrono::milliseconds(2));

        std::chrono::duration<double, std::milli> elapsed = sw.getElapsed();

        CHECK(elapsed.count() >= 1);
    }

    SECTION("Elapsed cast")
    {
        phi::StopWatch<std::chrono::system_clock> sw;

        std::this_thread::sleep_for(std::chrono::milliseconds(2));

        std::chrono::duration<std::int32_t, std::micro> elapsed =
                sw.getElapsed<std::int32_t, std::micro>();

        CHECK(elapsed.count() >= 1000);
    }
}
