#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_ABORT_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_ABORT_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/generated/compiler_support/features.hpp"

#if !defined(PHI_ABORT) && !defined(PHI_SUPPORTS_ABORT)
#    if PHI_HAS_INTRINSIC_BUILTIN_ABORT()
#        define PHI_ABORT()          __builtin_abort()
#        define PHI_SUPPORTS_ABORT() 1
#    else
#        define PHI_SUPPORTS_ABORT() 0
#    endif
#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_ABORT_HPP
