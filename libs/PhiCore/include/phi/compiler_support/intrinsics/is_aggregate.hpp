#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_AGGREGATE_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_AGGREGATE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/generated/compiler_support/features.hpp"

#if !defined(PHI_IS_AGGREGATE) && !defined(PHI_SUPPORTS_IS_AGGREGATE)
#    if PHI_HAS_INTRINSIC_IS_AGGREGATE()
#        define PHI_IS_AGGREGATE(type)      __is_aggregate(type)
#        define PHI_SUPPORTS_IS_AGGREGATE() 1
#    else
#        define PHI_SUPPORTS_IS_AGGREGATE() 0
#    endif

#    if defined(PHI_CONFIG_NO_INTRINSICS)
#        undef PHI_SUPPORTS_IS_AGGREGATE
#        define PHI_SUPPORTS_IS_AGGREGATE() 0
#    endif
#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_AGGREGATE_HPP
