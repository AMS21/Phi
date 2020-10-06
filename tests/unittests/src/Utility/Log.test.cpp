#include <Phi/Utility/Log.hpp>
#include <catch2/catch.hpp>
#include <spdlog/sinks/stdout_color_sinks.h>

#define TEST_ALL_LOG_MACROS()                                                                      \
    PHI_LOG_CORE_TRACE("Core trace");                                                              \
    PHI_LOG_CORE_DEBUG("Core debug");                                                              \
    PHI_LOG_CORE_INFO("Core info");                                                                \
    PHI_LOG_CORE_WARN("Core warn");                                                                \
    PHI_LOG_CORE_ERROR("Core error");                                                              \
    PHI_LOG_CORE_CRITICAL("Core critical");                                                        \
                                                                                                   \
    PHI_LOG_TRACE("Trace");                                                                        \
    PHI_LOG_DEBUG("Debug");                                                                        \
    PHI_LOG_INFO("Info");                                                                          \
    PHI_LOG_WARN("Warn");                                                                          \
    PHI_LOG_ERROR("Error");                                                                        \
    PHI_LOG_CRITICAL("Critical")

TEST_CASE("Log", "[Utility][Log]")
{
    SECTION("No registered logger")
    {
        TEST_ALL_LOG_MACROS();
    }

    SECTION("Default logger")
    {
        phi::Log::initialize_default_loggers();

        TEST_ALL_LOG_MACROS();

        phi::Log::UnregisterClientLogger();
        phi::Log::UnregisterCoreLogger();
    }

    SECTION("Custom logger")
    {
        std::shared_ptr<spdlog::logger> my_logger = spdlog::stderr_color_mt("Custom");

        phi::Log::RegisterClientLogger(my_logger);
        phi::Log::RegisterCoreLogger(my_logger);

        TEST_ALL_LOG_MACROS();

        phi::Log::UnregisterClientLogger();
        phi::Log::UnregisterCoreLogger();
    }
}
