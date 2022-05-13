#ifndef INCG_PHI_CORE_ASSERT_HPP
#define INCG_PHI_CORE_ASSERT_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/assume.hpp"
#include "phi/compiler_support/current_function.hpp"
#include "phi/compiler_support/likely.hpp"
#include "phi/compiler_support/unreachable.hpp"
#include "phi/compiler_support/warning.hpp"
#include "phi/preprocessor/source_line.hpp"
#include "phi/preprocessor/stringify.hpp"
#include <cstdlib>
#include <iostream>

DETAIL_PHI_BEGIN_NAMESPACE()

/// \cond detail
namespace detail
{
    inline constexpr const char* FormatArgument()
    {
        return "<None>";
    }

    template <typename... ArgsT>
    inline std::string FormatArgument(ArgsT&&... /*arg*/)
    {
        return {"<Disabled>"};
        /*
        return fmt::format(std::forward<ArgsT>(arg)...);
        */
    }
} // namespace detail
/// \endcond

DETAIL_PHI_END_NAMESPACE()

#define PHI_ASSERT(condition, ...)                                                                 \
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

#define PHI_ASSERT_NOT_REACHED() PHI_ASSERT(false, "This code should not be reachable.")

#define DETAIL_PHI_WRAPPED_ASSUME(condition)                                                       \
    PHI_BEGIN_MACRO()                                                                              \
    PHI_CLANG_SUPPRESS_WARNING_WITH_PUSH("-Wassume")                                               \
    PHI_MSVC_SUPPRESS_WARNING_WITH_PUSH(4557) /* '__assume' contains effect 'effect' */            \
    PHI_ASSUME(condition);                                                                         \
    PHI_MSVC_SUPPRESS_WARNING_POP()                                                                \
    PHI_CLANG_SUPPRESS_WARNING_POP()                                                               \
    PHI_END_MACRO()

#if defined(PHI_DEBUG)
#    define PHI_DBG_ASSERT(condition, ...) PHI_ASSERT(condition, __VA_ARGS__)
#    define PHI_DBG_ASSERT_NOT_REACHED()   PHI_ASSERT_NOT_REACHED()
#else
#    define PHI_DBG_ASSERT(condition, ...) DETAIL_PHI_WRAPPED_ASSUME(condition)
#    define PHI_DBG_ASSERT_NOT_REACHED()   PHI_UNREACHABLE()
#endif

#endif // INCG_PHI_CORE_ASSERT_HPP
