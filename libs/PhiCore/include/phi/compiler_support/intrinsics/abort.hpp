#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_ABORT_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_ABORT_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"

#if !defined(PHI_ABORT) && !defined(PHI_SUPPORTS_ABORT)

#    if PHI_COMPILER_IS(GCC) || PHI_COMPILER_IS(CLANG_COMPAT)
#        define PHI_ABORT()          __builtin_abort()
#        define PHI_SUPPORTS_ABORT() 1
#    else
#        define PHI_SUPPORTS_ABORT() 0
#    endif

#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_ABORT_HPP
