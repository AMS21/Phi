#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_REMOVE_POINTER_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_REMOVE_POINTER_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"

#if !defined(PHI_REMOVE_POINTER) && !defined(PHI_SUPPORTS_REMOVE_POINTER)

#    if PHI_COMPILER_IS_ATLEAST(CLANG, 16, 0, 0)
#        define PHI_REMOVE_POINTER(type)      __remove_pointer(type)
#        define PHI_SUPPORTS_REMOVE_POINTER() 1
#    else
#        define PHI_SUPPORTS_REMOVE_POINTER() 0
#    endif

#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_REMOVE_POINTER_HPP
