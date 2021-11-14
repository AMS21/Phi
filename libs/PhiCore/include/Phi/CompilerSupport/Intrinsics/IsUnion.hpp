#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_UNION_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_UNION_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Features.hpp"

#if PHI_HAS_INTRINSIC_IS_UNION()
#    define PHI_IS_UNION(type)      __is_union(type)
#    define PHI_SUPPORTS_IS_UNION() 1
#else
#    define PHI_IS_UNION(type)      false
#    define PHI_SUPPORTS_IS_UNION() 0
#endif

#if defined(PHI_CONFIG_NO_INTRINSICS)
#    undef PHI_SUPPORTS_IS_UNION
#    define PHI_SUPPORTS_IS_UNION() 0
#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_UNION_HPP
