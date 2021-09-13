#ifndef INCG_PHI_CONFIG_UNREACHABLE_HPP
#define INCG_PHI_CONFIG_UNREACHABLE_HPP

#include "Phi/CompilerSupport/Features.hpp"
#include "Phi/Config/FunctionLikeMacro.hpp"

#if PHI_HAS_EXTENSION_BUILTIN_UNREACHABLE()
#    define PHI_UNREACHABLE() __builtin_unreachable()
#elif PHI_HAS_EXTENSION_ASSUME()
#    define PHI_UNREACHABLE() __assume(0)
#elif PHI_HAS_EXTENSION_BUILTIN_ASSUME()
#    define PHI_UNREACHABLE() __builtin_assume(0)
#else
#    define PHI_UNREACHABLE() PHI_EMPTY_MACRO() /* Nothing */
#endif

#endif // INCG_PHI_CONFIG_UNREACHABLE_HPP
