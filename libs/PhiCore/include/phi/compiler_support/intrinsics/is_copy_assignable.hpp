#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_COPY_ASSIGNABLE_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_COPY_ASSIGNABLE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/generated/compiler_support/features.hpp"

#if !defined(PHI_IS_COPY_ASSIGNABLE) && !defined(PHI_SUPPORTS_IS_COPY_ASSIGNABLE)
#    if PHI_HAS_INTRINSIC_HAS_ASSIGN()
#        define PHI_IS_COPY_ASSIGNABLE(type)      __has_assign(type)
#        define PHI_SUPPORTS_IS_COPY_ASSIGNABLE() 1
#    else
#        define PHI_SUPPORTS_IS_COPY_ASSIGNABLE() 0
#    endif
#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_COPY_ASSIGNABLE_HPP
