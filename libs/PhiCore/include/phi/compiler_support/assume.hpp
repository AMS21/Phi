#ifndef INCG_PHI_CORE_COMPILER_SUPPORT_ASSUME_HPP
#define INCG_PHI_CORE_COMPILER_SUPPORT_ASSUME_HPP

#include "phi/compiler_support/features.hpp"
#include "phi/preprocessor/function_like_macro.hpp"

#if PHI_HAS_EXTENSION_ASSUME()
#    define PHI_ASSUME(condition) __assume(condition)
#elif PHI_HAS_EXTENSION_BUILTIN_ASSUME()
#    define PHI_ASSUME(condition) __builtin_assume(condition)
#elif PHI_HAS_EXTENSION_BUILTIN_UNREACHABLE()
// clang-format off
#    define PHI_ASSUME(condition) if (condition){} else __builtin_unreachable()
// clang-format on
#else
#    define PHI_ASSUME(condition) PHI_EMPTY_MACRO()
#endif

#endif // INCG_PHI_CORE_COMPILER_SUPPORT_ASSUME_HPP
