#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_DECAY_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_DECAY_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"

#if !defined(PHI_DECAY) && !defined(PHI_SUPPORTS_DECAY)

#    if PHI_COMPILER_IS_ATLEAST(CLANG, 16, 0, 0)
#        define PHI_DECAY(type)      __decay(type)
#        define PHI_SUPPORTS_DECAY() 1
#    else
#        define PHI_SUPPORTS_DECAY() 0
#    endif

#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_DECAY_HPP
