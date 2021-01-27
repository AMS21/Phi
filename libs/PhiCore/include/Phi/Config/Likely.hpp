#ifndef INCG_PHI_CONFIG_LIKELY_HPP
#define INCG_PHI_CONFIG_LIKELY_HPP

#include "Phi/Config/Compiler.hpp"
#include "Phi/Config/FunctionLikeMacro.hpp"

#if PHI_COMPILER_IS(GCC)
#    define PHI_LIKELY(condition)   __builtin_expect(!!(condition), 1)
#    define PHI_UNLIKELY(condition) __builtin_expect(!!(condition), 0)
#    if PHI_COMPILER_VERSION_IS_ATLEAST(9, 0, 0)
#        define PHI_LIKELY_CASE   [[likely]]
#        define PHI_UNLIKELY_CASE [[unlikely]]
#    else
#        define PHI_LIKELY_CASE   /* Nothing */
#        define PHI_UNLIKELY_CASE /* Nothing */
#    endif
#elif PHI_COMPILER_IS(CLANG)
#    if defined(__has_builtin) && __has_builtin(__builtin_expect)
#        define PHI_LIKELY(condition)   __builtin_expect(!!(condition), 1)
#        define PHI_UNLIKELY(condition) __builtin_expect(!!(condition), 0)
#    else
#        define PHI_LIKELY(condition)   condition
#        define PHI_UNLIKELY(condition) condition
#    endif
#    if PHI_COMPILER_VERSION_IS_ATLEAST(12, 0, 0)
#        define PHI_LIKELY_CASE   [[likely]]
#        define PHI_UNLIKELY_CASE [[unlikely]]
#    else
#        define PHI_LIKELY_CASE   /* Nothing */
#        define PHI_UNLIKELY_CASE /* Nothing */
#    endif
#elif PHI_COMPILER_IS_ATLEAST(MSVC, 19, 26, 0)
#    define PHI_LIKELY(condition)   condition
#    define PHI_UNLIKELY(condition) condition
#    define PHI_LIKELY_CASE         [[likely]]
#    define PHI_UNLIKELY_CASE       [[unlikely]]
#else
#    define PHI_LIKELY(condition)   condition
#    define PHI_UNLIKELY(condition) condition
#    define PHI_LIKELY_CASE         /* Nothing */
#    define PHI_UNLIKELY_CASE       /* Nothing */
#endif

#endif // INCG_PHI_CONFIG_LIKELY_HPP
