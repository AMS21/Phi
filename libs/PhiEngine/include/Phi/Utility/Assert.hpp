#ifndef INCG_PHI_UTILITY_ASSERT_HPP
#define INCG_PHI_UTILITY_ASSERT_HPP

#include "Phi/PhiConfig.hpp"
#include "Phi/Utility/Log.hpp"
#include <cpp/Assume.hpp>
#include <cpp/CurrentFunction.hpp>
#include <cpp/Likely.hpp>
#include <cpp/SourceLine.hpp>
#include <cpp/Stringify.hpp>
#include <cpp/Warning.hpp>
#include <spdlog/fmt/fmt.h>
#include <cstdlib>
#include <iostream>

DETAIL_PHI_BEGIN_NAMESPACE()

/// \cond detail
namespace detail
{
    inline const char* FormatArgument()
    {
        return "<None>";
    }

    template <typename... args>
    inline auto FormatArgument(args&&... arg) -> decltype(auto)
    {
        return fmt::format(std::forward<args>(arg)...);
    }
} // namespace detail
/// \endcond

DETAIL_PHI_END_NAMESPACE()

#define PHI_SIMPLE_ASSERT(condition, ...)                                                          \
    CPP_BEGIN_MACRO                                                                                \
    if (CPP_UNLIKELY(!(condition)))                                                                \
    {                                                                                              \
        ::std::cerr << "SIMPLE ASSERTION VIOLATION\n"                                              \
                    << "condition:\n " << CPP_STRINGIFY(condition) << '\n'                         \
                    << "file:\n " << __FILE__ << " (" << CPP_SOURCE_LINE << ")\n"                  \
                    << "function:\n " << CPP_CURRENT_FUNCTION << "\nadditional information:\n "    \
                    << ::phi::detail::FormatArgument(__VA_ARGS__);                                 \
                                                                                                   \
        ::std::abort();                                                                            \
    }                                                                                              \
    CPP_END_MACRO

#define PHI_ASSERT(condition, ...)                                                                 \
    CPP_BEGIN_MACRO                                                                                \
    if (CPP_UNLIKELY(!(condition)))                                                                \
    {                                                                                              \
        PHI_LOG_ERROR("ASSERTION VIOLATION\n"                                                      \
                      "condition:\n"                                                               \
                      " {}\n"                                                                      \
                      "file:\n"                                                                    \
                      " {} ({})\n"                                                                 \
                      "function:\n"                                                                \
                      " {}\n"                                                                      \
                      "additional information:\n"                                                  \
                      " {}",                                                                       \
                      CPP_STRINGIFY(condition), __FILE__, CPP_SOURCE_LINE, CPP_CURRENT_FUNCTION,   \
                      ::phi::detail::FormatArgument(__VA_ARGS__));                                 \
                                                                                                   \
        ::std::abort();                                                                            \
    }                                                                                              \
    CPP_END_MACRO

#define DETAIL_PHI_WRAPPED_ASSUME(condition)                                                       \
    CPP_BEGIN_MACRO                                                                                \
    CPP_CLANG_SUPPRESS_WARNING_WITH_PUSH("-Wassume")                                               \
    CPP_ASSUME(condition);                                                                         \
    CPP_CLANG_SUPPRESS_WARNING_POP                                                                 \
    CPP_END_MACRO

#if defined(PHI_DEBUG)
#    define PHI_DBG_ASSERT(condition, ...) PHI_ASSERT(condition, __VA_ARGS__)
#    define PHI_DBG_SIMPLE_ASSERT(condition, ...) PHI_SIMPLE_ASSERT(condition, __VA_ARGS__)
#else
#    define PHI_DBG_ASSERT(condition, ...) DETAIL_PHI_WRAPPED_ASSUME(condition)
#    define PHI_DBG_SIMPLE_ASSERT(condition, ...) DETAIL_PHI_WRAPPED_ASSUME(condition)
#endif

#endif // INCG_PHI_UTILITY_ASSERT_HPP
