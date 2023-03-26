#ifndef INCG_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_OFFSETOF_HPP
#define INCG_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_OFFSETOF_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"

#if !defined(PHI_OFFSETOF) && !defined(PHI_SUPPORTS_OFFSETOF)

#    if PHI_COMPILER_IS(GCC) || PHI_COMPILER_IS(CLANG_COMPAT) ||                                   \
            PHI_COMPILER_IS_ATLEAST(MSVC, 19, 14, 0)
#        define PHI_OFFSETOF(type, member) __builtin_offsetof(type, member)
#        define PHI_SUPPORTS_OFFSETOF()    1
#    else
#        define PHI_SUPPORTS_OFFSETOF() 0
#    endif

#endif

#endif // INCG_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_OFFSETOF_HPP
