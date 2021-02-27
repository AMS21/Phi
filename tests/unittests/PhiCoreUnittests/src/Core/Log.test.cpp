#include <catch2/catch_test_macros.hpp>

#include <Phi/Config/Warning.hpp>
#include <Phi/Core/Log.hpp>

PHI_EXTERNAL_HEADERS_BEGIN()
#include <spdlog/sinks/stdout_color_sinks.h>
#include <memory>
PHI_EXTERNAL_HEADERS_END()

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

        phi::Log::unregister_client_logger();
        phi::Log::unregister_core_logger();
    }

    SECTION("Custom logger")
    {
        std::shared_ptr<spdlog::logger> my_logger = spdlog::stderr_color_mt("Custom");

        phi::Log::register_client_logger(my_logger);
        phi::Log::register_core_logger(my_logger);

        TEST_ALL_LOG_MACROS();

        phi::Log::unregister_client_logger();
        phi::Log::unregister_core_logger();
    }
}
