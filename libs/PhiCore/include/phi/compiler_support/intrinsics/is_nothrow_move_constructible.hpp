#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_NOTHROW_MOVE_CONSTRUCTIBLE_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_NOTHROW_MOVE_CONSTRUCTIBLE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/generated/compiler_support/features.hpp"

#if !defined(PHI_IS_NOTHROW_MOVE_CONSTRUCTIBLE) &&                                                 \
        !defined(PHI_SUPPORTS_IS_NOTHROW_MOVE_CONSTRUCTIBLE)
#    if PHI_HAS_INTRINSIC_HAS_NOTHROW_MOVE_CONSTRUCTOR() && PHI_COMPILER_IS(MSVC)
#        define PHI_IS_NOTHROW_MOVE_CONSTRUCTIBLE(type)      __has_nothrow_move_constructor(type)
#        define PHI_SUPPORTS_IS_NOTHROW_MOVE_CONSTRUCTIBLE() 1
#    else
#        define PHI_SUPPORTS_IS_NOTHROW_MOVE_CONSTRUCTIBLE() 0
#    endif
#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_NOTHROW_MOVE_CONSTRUCTIBLE_HPP
