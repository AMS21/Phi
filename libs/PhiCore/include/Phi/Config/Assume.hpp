#ifndef INCG_PHI_CONFIG_ASSUME_HPP
#define INCG_PHI_CONFIG_ASSUME_HPP

#include "Phi/CompilerSupport/Features.hpp"
#include "Phi/Config/FunctionLikeMacro.hpp"

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

#endif // INCG_PHI_CONFIG_ASSUME_HPP
