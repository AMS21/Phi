#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_COMPOUND_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_COMPOUND_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"

#if !defined(PHI_IS_COMPUND) && !defined(PHI_SUPPORTS_IS_COMPUND)

#    if PHI_COMPILER_IS(CLANG_COMPAT)
#        define PHI_IS_COMPOUND(type)      __is_compound(type)
#        define PHI_SUPPORTS_IS_COMPOUND() 1
#    else
#        define PHI_SUPPORTS_IS_COMPOUND() 0
#    endif

#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_COMPOUND_HPP
