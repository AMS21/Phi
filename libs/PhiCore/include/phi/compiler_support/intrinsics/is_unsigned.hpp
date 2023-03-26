#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_UNSIGNED_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_UNSIGNED_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"

#if !defined(PHI_IS_UNSIGNED) && !defined(PHI_SUPPORTS_IS_UNSIGNED)

#    if PHI_COMPILER_IS(CLANG_COMPAT)
#        define PHI_IS_UNSIGNED(type)      __is_unsigned(type)
#        define PHI_SUPPORTS_IS_UNSIGNED() 1
#    else
#        define PHI_SUPPORTS_IS_UNSIGNED() 0
#    endif

#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_UNSIGNED_HPP
