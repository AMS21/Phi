#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_TRIVIALLY_DESTRUCTIBLE_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_TRIVIALLY_DESTRUCTIBLE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/generated/compiler_support/features.hpp"

#if !defined(PHI_IS_TRIVIALLY_DESTRUCTIBLE) && !defined(PHI_SUPPORTS_IS_TRIVIALLY_DESTRUCTIBLE)
#    if PHI_HAS_INTRINSIC_IS_TRIVIALLY_DESTRUCTIBLE()
#        define PHI_IS_TRIVIALLY_DESTRUCTIBLE(type)      __is_trivially_destructible(type)
#        define PHI_SUPPORTS_IS_TRIVIALLY_DESTRUCTIBLE() 1
#    elif PHI_HAS_INTRINSIC_HAS_TRIVIAL_DESTRUCTOR() && PHI_COMPILER_IS(MSVC)
#        define PHI_IS_TRIVIALLY_DESTRUCTIBLE(type)      __has_trivial_destructor(type)
#        define PHI_SUPPORTS_IS_TRIVIALLY_DESTRUCTIBLE() 1
#    else
#        define PHI_SUPPORTS_IS_TRIVIALLY_DESTRUCTIBLE() 0
#    endif
#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_TRIVIALLY_DESTRUCTIBLE_HPP
