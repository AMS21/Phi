#ifndef INCG_PHI_CORE_TYPE_TRAITS_DETAIL_INTRINSICS_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_DETAIL_INTRINSICS_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Features.hpp"

// GCCs implementation of __is_constructible is bugged
// See: TODO insert link
#if PHI_HAS_INTRINSIC_IS_CONSTRUCTIBLE() && PHI_COMPILER_IS_NOT(GCC) &&                            \
        !defined(PHI_CONFIG_NO_INTRINSICS)
#    define PHI_TYPE_TRAITS_USE_INTRINSIC_IS_CONSTRUCTIBLE() 1
#    define PHI_IS_CONSTRUCTIBLE(X)                          __is_constructible(x)
#else
#    define PHI_TYPE_TRAITS_USE_INTRINSIC_IS_CONSTRUCTIBLE() 0
#    define PHI_IS_CONSTRUCTIBLE(x)                          false
#endif

#endif // INCG_PHI_CORE_TYPE_TRAITS_DETAIL_INTRINSICS_HPP
