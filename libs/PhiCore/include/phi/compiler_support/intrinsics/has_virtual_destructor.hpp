#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_HAS_VIRTUAL_DESTRUCTOR_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_HAS_VIRTUAL_DESTRUCTOR_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/generated/compiler_support/features.hpp"

#if !defined(PHI_HAS_VIRTUAL_DESTRUCTOR) && !defined(PHI_SUPPORTS_HAS_VIRTUAL_DESTRUCTOR)
#    if PHI_HAS_INTRINSIC_HAS_VIRTUAL_DESTRUCTOR()
#        define PHI_HAS_VIRTUAL_DESTRUCTOR(obj)       __has_virtual_destructor(obj)
#        define PHI_SUPPORTS_HAS_VIRTUAL_DESTRUCTOR() 1
#    else
#        define PHI_SUPPORTS_HAS_VIRTUAL_DESTRUCTOR() 0
#    endif
#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_HAS_VIRTUAL_DESTRUCTOR_HPP
