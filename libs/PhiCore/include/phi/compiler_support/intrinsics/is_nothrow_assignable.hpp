#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_NOTHROW_ASSIGNABLE_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_NOTHROW_ASSIGNABLE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/generated/compiler_support/features.hpp"

#if !defined(PHI_IS_NOTHROW_ASSIGNABLE) && !defined(PHI_SUPPORTS_IS_NOTHROW_ASSIGNABLE)
#    if PHI_HAS_INTRINSIC_IS_NOTHROW_ASSIGNABLE()
#        define PHI_IS_NOTHROW_ASSIGNABLE(type, with_type) __is_nothrow_assignable(type, with_type)
#        define PHI_SUPPORTS_IS_NOTHROW_ASSIGNABLE()       1
#    else
#        define PHI_SUPPORTS_IS_NOTHROW_ASSIGNABLE() 0
#    endif
#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_NOTHROW_ASSIGNABLE_HPP
