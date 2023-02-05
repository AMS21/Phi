#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_FLOORF_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_FLOORF_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/generated/compiler_support/features.hpp"

#if !defined(PHI_FLOORF) && !defined(PHI_SUPPORTS_FLOORF)
#    if PHI_HAS_INTRINSIC_BUILTIN_FLOORF()
#        define PHI_FLOORF(value)     __builtin_floorf(value)
#        define PHI_SUPPORTS_FLOORF() 1
#    else
#        define PHI_SUPPORTS_FLOORF() 0
#    endif
#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_FLOORF_HPP
