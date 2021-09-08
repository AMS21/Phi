#ifndef INCG_PHI_CORE_COMPILER_SUPPORT_INLINE_VARIABLES_HPP
#define INCG_PHI_CORE_COMPILER_SUPPORT_INLINE_VARIABLES_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/Config/CPlusPlus.hpp"
#include "Phi/Config/Compiler.hpp"

#if PHI_CPP_STANDARD_IS_ATLEAST(17) &&                                                             \
        (PHI_COMPILER_IS_ATLEAST(CLANG, 3, 9, 0) || PHI_COMPILER_IS_ATLEAST(GCC, 7, 0, 0) ||       \
         PHI_COMPILER_IS_ATLEAST(MSVC, 19, 12, 0))
#    define PHI_HAS_INLINE_VARIABLES()          1
#    define PHI_INLINE_VARIABLE                 inline
#    define PHI_INLINE_VARIABLE_OR(alternative) inline
#else
#    define PHI_HAS_INLINE_VARIABLES()          0
#    define PHI_INLINE_VARIABLE                 /* Nothing */
#    define PHI_INLINE_VARIABLE_OR(alternative) alternative
#endif

#endif // INCG_PHI_CORE_COMPILER_SUPPORT_INLINE_VARIABLES_HPP
