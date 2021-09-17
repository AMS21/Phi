#ifndef INCG_PHI_UTILITY_LOG_HPP
#define INCG_PHI_UTILITY_LOG_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Nodiscard.hpp"
#include "Phi/Config/FunctionLikeMacro.hpp"
#include "Phi/Config/Warning.hpp"

PHI_EXTERNAL_HEADERS_BEGIN()
#include <spdlog/spdlog.h>
#include <memory>
PHI_EXTERNAL_HEADERS_END()

DETAIL_PHI_BEGIN_NAMESPACE()

class Log
{
public:
    PHI_NODISCARD static std::shared_ptr<spdlog::logger> get_core_logger() noexcept;

    PHI_NODISCARD static std::shared_ptr<spdlog::logger> get_client_logger() noexcept;

    static void initialize_default_loggers() noexcept;

    static void register_core_logger(const std::shared_ptr<spdlog::logger>& logger) noexcept;

    static void register_client_logger(const std::shared_ptr<spdlog::logger>& logger) noexcept;

    static void unregister_core_logger() noexcept;

    static void unregister_client_logger() noexcept;

private:
    static std::shared_ptr<spdlog::logger> s_CoreLogger;
    static std::shared_ptr<spdlog::logger> s_ClientLogger;
}; // namespace Log

DETAIL_PHI_END_NAMESPACE()

#if defined(PHI_CONFIG_ENABLE_LOGGING)
#    define PHI_LOG_TRACE(...) SPDLOG_LOGGER_TRACE(::phi::Log::get_client_logger(), __VA_ARGS__)
#    define PHI_LOG_DEBUG(...) SPDLOG_LOGGER_DEBUG(::phi::Log::get_client_logger(), __VA_ARGS__)
#    define PHI_LOG_INFO(...)  SPDLOG_LOGGER_INFO(::phi::Log::get_client_logger(), __VA_ARGS__)
#    define PHI_LOG_WARN(...)  SPDLOG_LOGGER_WARN(::phi::Log::get_client_logger(), __VA_ARGS__)
#    define PHI_LOG_ERROR(...) SPDLOG_LOGGER_ERROR(::phi::Log::get_client_logger(), __VA_ARGS__)
#    define PHI_LOG_CRITICAL(...)                                                                  \
        SPDLOG_LOGGER_CRITICAL(::phi::Log::get_client_logger(), __VA_ARGS__)
#else
#    define PHI_LOG_TRACE(...)    PHI_EMPTY_MACRO
#    define PHI_LOG_DEBUG(...)    PHI_EMPTY_MACRO
#    define PHI_LOG_INFO(...)     PHI_EMPTY_MACRO
#    define PHI_LOG_WARN(...)     PHI_EMPTY_MACRO
#    define PHI_LOG_ERROR(...)    PHI_EMPTY_MACRO
#    define PHI_LOG_CRITICAL(...) PHI_EMPTY_MACRO
#endif

#if defined(PHI_CONFIG_ENABLE_INTERNAL_LOGGING)
#    define PHI_LOG_CORE_TRACE(...) SPDLOG_LOGGER_TRACE(::phi::Log::get_core_logger(), __VA_ARGS__)
#    define PHI_LOG_CORE_DEBUG(...) SPDLOG_LOGGER_DEBUG(::phi::Log::get_core_logger(), __VA_ARGS__)
#    define PHI_LOG_CORE_INFO(...)  SPDLOG_LOGGER_INFO(::phi::Log::get_core_logger(), __VA_ARGS__)
#    define PHI_LOG_CORE_WARN(...)  SPDLOG_LOGGER_WARN(::phi::Log::get_core_logger(), __VA_ARGS__)
#    define PHI_LOG_CORE_ERROR(...) SPDLOG_LOGGER_ERROR(::phi::Log::get_core_logger(), __VA_ARGS__)
#    define PHI_LOG_CORE_CRITICAL(...)                                                             \
        SPDLOG_LOGGER_CRITICAL(::phi::Log::get_core_logger(), __VA_ARGS__)
#else
#    define PHI_LOG_CORE_TRACE(...)    PHI_EMPTY_MACRO
#    define PHI_LOG_CORE_DEBUG(...)    PHI_EMPTY_MACRO
#    define PHI_LOG_CORE_INFO(...)     PHI_EMPTY_MACRO
#    define PHI_LOG_CORE_WARN(...)     PHI_EMPTY_MACRO
#    define PHI_LOG_CORE_ERROR(...)    PHI_EMPTY_MACRO
#    define PHI_LOG_CORE_CRITICAL(...) PHI_EMPTY_MACRO
#endif

#endif // INCG_PHI_UTILITY_LOG_HPP
