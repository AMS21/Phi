#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_REFERENCEABLE_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_REFERENCEABLE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"

#if !defined(PHI_IS_REFERENCEABLE) && !defined(PHI_SUPPORTS_IS_REFERENCEABLE)

#    if PHI_COMPILER_IS_ATLEAST(CLANG, 16, 0, 0)
#        define PHI_IS_REFERENCEABLE(type)      __is_referenceable(type)
#        define PHI_SUPPORTS_IS_REFERENCEABLE() 1
#    else
#        define PHI_SUPPORTS_IS_REFERENCEABLE() 0
#    endif

#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_REFERENCEABLE_HPP
