#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_MAKE_SIGNED_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_MAKE_SIGNED_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"

#if !defined(PHI_MAKE_SIGNED) && !defined(PHI_SUPPORTS_MAKE_SIGNED)

#    if PHI_COMPILER_IS_ATLEAST(CLANG, 16, 0, 0)
#        define PHI_MAKE_SIGNED(type)      __make_signed(type)
#        define PHI_SUPPORTS_MAKE_SIGNED() 1
#    else
#        define PHI_SUPPORTS_MAKE_SIGNED() 0
#    endif

#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_MAKE_SIGNED_HPP
