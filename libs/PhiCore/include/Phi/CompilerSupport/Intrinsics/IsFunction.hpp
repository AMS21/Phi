#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_FUNCTION_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_FUNCTION_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Features.hpp"

#if PHI_HAS_INTRINSIC_IS_FUNCTION()
#    define PHI_IS_FUNCTION(type)      __is_function(type)
#    define PHI_SUPPORTS_IS_FUNCTION() 1
#else
#    define PHI_IS_FUNCTION(type)      false
#    define PHI_SUPPORTS_IS_FUNCTION() 0
#endif

#if defined(PHI_CONFIG_NO_INTRINSICS)
#    undef PHI_SUPPORTS_IS_FUNCTION
#    define PHI_SUPPORTS_IS_FUNCTION() 0
#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_FUNCTION_HPP
