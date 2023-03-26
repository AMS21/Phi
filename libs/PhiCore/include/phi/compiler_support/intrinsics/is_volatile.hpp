#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_VOLATILE_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_VOLATILE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"

#if !defined(PHI_IS_VOLATILE) && !defined(PHI_SUPPORTS_IS_VOLATILE)

#    if PHI_COMPILER_IS(CLANG_COMPAT)
#        define PHI_IS_VOLATILE(type)      __is_volatile(type)
#        define PHI_SUPPORTS_IS_VOLATILE() 1
#    else
#        define PHI_SUPPORTS_IS_VOLATILE() 0
#    endif

#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_VOLATILE_HPP
