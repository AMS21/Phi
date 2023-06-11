#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_MAKE_UNSIGNED_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_MAKE_UNSIGNED_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"

#if !defined(PHI_MAKE_UNSIGNED) && !defined(PHI_SUPPORTS_MAKE_UNSIGNED)

#    if PHI_COMPILER_IS_ATLEAST(CLANG, 16, 0, 0)
#        define PHI_MAKE_UNSIGNED(type)      __make_unsigned(type)
#        define PHI_SUPPORTS_MAKE_UNSIGNED() 1
#    else
#        define PHI_SUPPORTS_MAKE_UNSIGNED() 0
#    endif

#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_MAKE_UNSIGNED_HPP
