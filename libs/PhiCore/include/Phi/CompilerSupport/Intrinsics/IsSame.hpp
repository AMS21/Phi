#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_SAME_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_SAME_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Features.hpp"

#if PHI_HAS_INTRINSIC_IS_SAME()
#    define PHI_IS_SAME(lhs, rhs)  __is_same(lhs, rhs)
#    define PHI_SUPPORTS_IS_SAME() 1
#elif PHI_HAS_INTRINSIC_IS_SAME_AS()
#    define PHI_IS_SAME(lhs, rhs)  __is_same_as(lhs, rhs)
#    define PHI_SUPPORTS_IS_SAME() 1
#else
#    define PHI_IS_SAME(lhs, rhs)  false
#    define PHI_SUPPORTS_IS_SAME() 0
#endif

#if defined(PHI_CONFIG_NO_INTRINSICS)
#    undef PHI_SUPPORTS_IS_SAME
#    define PHI_SUPPORTS_IS_SAME() 0
#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_SAME_HPP
