#ifndef INCG_PHI_CORE_ASSERT_HPP
#define INCG_PHI_CORE_ASSERT_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/assume.hpp"
#include "phi/compiler_support/current_function.hpp"
#include "phi/compiler_support/likely.hpp"
#include "phi/compiler_support/noreturn.hpp"
#include "phi/compiler_support/unreachable.hpp"
#include "phi/compiler_support/warning.hpp"
#include "phi/preprocessor/function_like_macro.hpp"
#include "phi/type_traits/is_constant_evaluated.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

/// \cond detail
namespace detail
{
    PHI_NORETURN extern void phi_assert_failure_handler(const char* condition, const char* file,
                                                        int         line_number,
                                                        const char* function) noexcept;
} // namespace detail
/// \endcond

DETAIL_PHI_END_NAMESPACE()

#define DETAIL_PHI_WRAPPED_ASSUME(condition)                                                       \
    PHI_BEGIN_MACRO()                                                                              \
    PHI_CLANG_SUPPRESS_WARNING_WITH_PUSH("-Wassume")                                               \
    PHI_MSVC_SUPPRESS_WARNING_WITH_PUSH(4557) /* '__assume' contains effect 'effect' */            \
    PHI_ASSUME(condition);                                                                         \
    PHI_MSVC_SUPPRESS_WARNING_POP()                                                                \
    PHI_CLANG_SUPPRESS_WARNING_POP()                                                               \
    PHI_END_MACRO()

#define PHI_RELEASE_ASSERT(condition, ...)                                                         \
    PHI_BEGIN_MACRO()                                                                              \
    PHI_GCC_SUPPRESS_WARNING_WITH_PUSH("-Wuseless-cast")                                           \
    if (PHI_UNLIKELY(!static_cast<bool>(condition)))                                               \
    {                                                                                              \
        ::phi::detail::phi_assert_failure_handler(#condition, __FILE__, __LINE__,                  \
                                                  PHI_CURRENT_FUNCTION());                         \
    }                                                                                              \
    PHI_GCC_SUPPRESS_WARNING_POP()                                                                 \
    PHI_END_MACRO()

#if PHI_CONFIG_ENABLE_ASSERTIONS
#    define PHI_ASSERT(condition, ...) PHI_RELEASE_ASSERT(condition, __VA_ARGS__)
#else
#    define PHI_ASSERT(condition, ...)                                                             \
        PHI_BEGIN_MACRO()                                                                          \
        DETAIL_PHI_WRAPPED_ASSUME(condition);                                                      \
        PHI_GCC_SUPPRESS_WARNING_WITH_PUSH("-Wuseless-cast")                                       \
        if (::phi::is_constant_evaluated() && !static_cast<bool>(condition))                       \
        {                                                                                          \
            ::phi::detail::phi_assert_failure_handler(#condition, __FILE__, __LINE__,              \
                                                      PHI_CURRENT_FUNCTION());                     \
            PHI_UNREACHABLE();                                                                     \
        }                                                                                          \
        PHI_GCC_SUPPRESS_WARNING_POP()                                                             \
        PHI_END_MACRO()
#endif

#define PHI_ASSERT_NOT_REACHED() PHI_ASSERT(false, "This code should not be reachable")

#define PHI_RELEASE_ASSERT_NOT_REACHED()                                                           \
    PHI_RELEASE_ASSERT(false, "This code should not be reachable")

#endif // INCG_PHI_CORE_ASSERT_HPP
