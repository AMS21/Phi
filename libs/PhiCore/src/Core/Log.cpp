#include "Phi/Core/Log.hpp"

#include "Phi/PhiConfig.hpp"
#include <spdlog/common.h>
#include <spdlog/logger.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/null_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

DETAIL_PHI_BEGIN_NAMESPACE()

std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

constexpr const char DefaultFormattingString[]{"%^[%Y-%m-%d %H:%M:%S.%e] %n [%L](%s:%#):%$ %v"};

std::shared_ptr<spdlog::logger> Log::get_core_logger() noexcept
{
    if (!s_CoreLogger)
    {
        spdlog::drop("Phi");
        s_CoreLogger = spdlog::null_logger_mt("Phi");
    }

    return s_CoreLogger;
}

std::shared_ptr<spdlog::logger> Log::get_client_logger() noexcept
{
    if (!s_ClientLogger)
    {
        spdlog::drop("Client");
        s_ClientLogger = spdlog::null_logger_mt("Client");
    }

    return s_ClientLogger;
}

void Log::initialize_default_loggers() noexcept
{
    // Unregister the current loggers
    unregister_core_logger();
    unregister_client_logger();

    // Create sinks
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(spdlog::level::trace);

    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("Phi.log", true);
    file_sink->set_level(spdlog::level::trace);

    // Core logger
    s_CoreLogger = std::make_shared<spdlog::logger>(
            "Phi", spdlog::sinks_init_list{console_sink, file_sink});
    s_CoreLogger->set_pattern(DefaultFormattingString);
    s_CoreLogger->set_level(spdlog::level::trace);
    s_CoreLogger->flush_on(spdlog::level::err);

    // Client logger
    s_ClientLogger = std::make_shared<spdlog::logger>(
            "Client", spdlog::sinks_init_list{console_sink, file_sink});
    s_ClientLogger->set_pattern(DefaultFormattingString);
    s_ClientLogger->set_level(spdlog::level::trace);
    s_ClientLogger->flush_on(spdlog::level::err);
}

void Log::register_core_logger(const std::shared_ptr<spdlog::logger>& logger) noexcept
{
    s_CoreLogger = logger;
}

void Log::register_client_logger(const std::shared_ptr<spdlog::logger>& logger) noexcept
{
    s_ClientLogger = logger;
}

void Log::unregister_core_logger() noexcept
{
    if (s_CoreLogger)
    {
        spdlog::drop(s_CoreLogger->name());
    }

    s_CoreLogger = nullptr;
}

void Log::unregister_client_logger() noexcept
{
    if (s_ClientLogger)
    {
        spdlog::drop(s_ClientLogger->name());
    }

    s_ClientLogger = nullptr;
}

DETAIL_PHI_END_NAMESPACE()
