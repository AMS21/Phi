#ifndef INCG_PHI_UTILITY_ASSERT_HPP
#define INCG_PHI_UTILITY_ASSERT_HPP

#include "Phi/Config/Assume.hpp"
#include "Phi/Config/CurrentFunction.hpp"
#include "Phi/Config/Likely.hpp"
#include "Phi/Config/SourceLine.hpp"
#include "Phi/Config/Stringify.hpp"
#include "Phi/Config/Warning.hpp"
#include "Phi/Core/Log.hpp"
#include "Phi/PhiConfig.hpp"
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

    template <typename... ArgsT>
    inline auto FormatArgument(ArgsT&&... arg) -> decltype(auto)
    {
        return fmt::format(std::forward<ArgsT>(arg)...);
    }
} // namespace detail
/// \endcond

DETAIL_PHI_END_NAMESPACE()

#define PHI_SIMPLE_ASSERT(condition, ...)                                                          \
    PHI_BEGIN_MACRO()                                                                              \
    if (PHI_UNLIKELY(!(condition)))                                                                \
    {                                                                                              \
        ::std::cerr << "SIMPLE ASSERTION VIOLATION\n"                                              \
                    << "condition:\n " << PHI_STRINGIFY(condition) << '\n'                         \
                    << "file:\n " << __FILE__ << " (" << PHI_SOURCE_LINE() << ")\n"                \
                    << "function:\n " << PHI_CURRENT_FUNCTION() << "\nadditional information:\n "  \
                    << ::phi::detail::FormatArgument(__VA_ARGS__);                                 \
                                                                                                   \
        ::std::abort();                                                                            \
    }                                                                                              \
    PHI_END_MACRO()

#define PHI_ASSERT(condition, ...)                                                                 \
    PHI_BEGIN_MACRO()                                                                              \
    if (PHI_UNLIKELY(!(condition)))                                                                \
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
                      PHI_STRINGIFY(condition), __FILE__, PHI_SOURCE_LINE(),                       \
                      PHI_CURRENT_FUNCTION(), ::phi::detail::FormatArgument(__VA_ARGS__));         \
                                                                                                   \
        ::std::abort();                                                                            \
    }                                                                                              \
    PHI_END_MACRO()

#define DETAIL_PHI_WRAPPED_ASSUME(condition)                                                       \
    PHI_BEGIN_MACRO()                                                                              \
    PHI_CLANG_SUPPRESS_WARNING_WITH_PUSH("-Wassume")                                               \
    PHI_ASSUME(condition);                                                                         \
    PHI_CLANG_SUPPRESS_WARNING_POP()                                                               \
    PHI_END_MACRO()

#if defined(PHI_DEBUG)
#    define PHI_DBG_ASSERT(condition, ...)        PHI_ASSERT(condition, __VA_ARGS__)
#    define PHI_DBG_SIMPLE_ASSERT(condition, ...) PHI_SIMPLE_ASSERT(condition, __VA_ARGS__)
#else
#    define PHI_DBG_ASSERT(condition, ...)        DETAIL_PHI_WRAPPED_ASSUME(condition)
#    define PHI_DBG_SIMPLE_ASSERT(condition, ...) DETAIL_PHI_WRAPPED_ASSUME(condition)
#endif

#endif // INCG_PHI_UTILITY_ASSERT_HPP
