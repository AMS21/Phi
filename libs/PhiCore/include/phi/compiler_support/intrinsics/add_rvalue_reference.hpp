#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_ADD_RVALUE_REFERENCE_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_ADD_RVALUE_REFERENCE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"

#if !defined(PHI_ADD_RVALUE_REFERENCE) && !defined(PHI_SUPPORTS_ADD_RVALUE_REFERENCE)

#    if PHI_COMPILER_IS_ATLEAST(CLANG, 16, 0, 0)
#        define PHI_ADD_RVALUE_REFERENCE(type)      __add_rvalue_reference(type)
#        define PHI_SUPPORTS_ADD_RVALUE_REFERENCE() 1
#    else
#        define PHI_SUPPORTS_ADD_RVALUE_REFERENCE() 0
#    endif

#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_ADD_RVALUE_REFERENCE_HPP
