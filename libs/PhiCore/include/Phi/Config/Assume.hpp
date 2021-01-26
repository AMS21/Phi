#ifndef INCG_PHI_CONFIG_ASSUME_HPP
#define INCG_PHI_CONFIG_ASSUME_HPP

#include "Phi/Config/Compiler.hpp"
#include "Phi/Config/FunctionLikeMacro.hpp"

#if PHI_COMPILER_IS(MSVC)
#    define PHI_ASSUME(condition) __assume(condition)
#elif PHI_COMPILER_IS(CLANG) && defined(__has_builtin)
#    if __has_builtin(__builtin_assume)
#        define PHI_ASSUME(condition) __builtin_assume(condition)
#    elif __has_builtin(__builtin_unreachable)
// clang-format off
#        define PHI_ASSUME(condition) if (condition){} else __builtin_unreachable()
// clang-format on
#    else
#        define PHI_ASSUME(condition) PHI_EMPTY_MACRO()
#    endif
#elif PHI_COMPILER_IS_ATLEAST(GCC, 4, 5, 3)
// clang-format off
#   define PHI_ASSUME(condition) if (condition){} else __builtin_unreachable()
// clang-format on
#else
#    define PHI_ASSUME(condition) PHI_EMPTY_MACRO()
#endif

#endif // INCG_PHI_CONFIG_ASSUME_HPP
