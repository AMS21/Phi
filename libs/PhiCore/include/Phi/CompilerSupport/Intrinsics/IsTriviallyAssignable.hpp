#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_TRIVIALLY_ASSIGNABLE_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_TRIVIALLY_ASSIGNABLE_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Features.hpp"

#if PHI_HAS_INTRINSIC_IS_TRIVIALLY_ASSIGNABLE()
#    define PHI_IS_TRIVIALLY_ASSIGNABLE(type, with_type) __is_trivially_assignable(type, with_type)
#    define PHI_SUPPORTS_IS_TRIVIALLY_ASSIGNABLE()       1
#else
#    define PHI_IS_TRIVIALLY_ASSIGNABLE(type, with_type) false
#    define PHI_SUPPORTS_IS_TRIVIALLY_ASSIGNABLE()       0
#endif

#if defined(PHI_CONFIG_NO_INTRINSICS)
#    undef PHI_SUPPORTS_IS_TRIVIALLY_ASSIGNABLE
#    define PHI_SUPPORTS_IS_TRIVIALLY_ASSIGNABLE() 0
#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_TRIVIALLY_ASSIGNABLE_HPP
