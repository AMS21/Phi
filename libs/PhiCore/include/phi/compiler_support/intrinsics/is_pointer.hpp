#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_POINTER_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_POINTER_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"
#include "phi/generated/compiler_support/features.hpp"

#if !defined(PHI_IS_POINTER) && !defined(PHI_SUPPORTS_IS_POINTER)
#    if PHI_HAS_INTRINSIC_IS_POINTER() && PHI_HAS_KEYWORD(__is_pointer) &&                         \
            !PHI_COMPILER_IS_BELOW(CLANG, 10, 0, 0)
#        define PHI_IS_POINTER(type)      __is_pointer(type)
#        define PHI_SUPPORTS_IS_POINTER() 1
#    else
#        define PHI_IS_POINTER(type)      false
#        define PHI_SUPPORTS_IS_POINTER() 0
#    endif

#    if defined(PHI_CONFIG_NO_INTRINSICS)
#        undef PHI_SUPPORTS_IS_POINTER
#        define PHI_SUPPORTS_IS_POINTER() 0
#    endif
#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_POINTER_HPP
