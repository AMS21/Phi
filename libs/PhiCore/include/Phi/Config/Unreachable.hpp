#ifndef INCG_PHI_CONFIG_UNREACHABLE_HPP
#define INCG_PHI_CONFIG_UNREACHABLE_HPP

#include "Phi/Config/Assume.hpp"
#include "Phi/Config/Compiler.hpp"
#include "Phi/Config/FunctionLikeMacro.hpp"

#if PHI_COMPILER_IS(MSVC)
#    define PHI_UNREACHABLE() PHI_ASSUME(0)
#elif PHI_COMPILER_IS(CLANG)
#    if defined(__has_builtin) && __has_builtin(__builtin_unreachable)
#        define PHI_UNREACHABLE() __builtin_unreachable()
#    else
#        define PHI_UNREACHABLE() PHI_ASSUME(0)
#    endif
#elif PHI_COMPILER_IS_ATLEAST(GCC, 4, 5, 3)
#    define PHI_UNREACHABLE() __builtin_unreachable()
#else
#    define PHI_UNREACHABLE() PHI_EMPTY_MACRO() /* Nothing */
#endif

#endif // INCG_PHI_CONFIG_UNREACHABLE_HPP
