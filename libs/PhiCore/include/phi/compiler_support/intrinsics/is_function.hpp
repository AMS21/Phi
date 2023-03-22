#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_FUNCTION_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_FUNCTION_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"

#if !defined(PHI_IS_FUNCTION) && !defined(PHI_SUPPORTS_IS_FUNCTION)

#    if PHI_COMPILER_IS(CLANG_COMPAT)
#        define PHI_IS_FUNCTION(type)      __is_function(type)
#        define PHI_SUPPORTS_IS_FUNCTION() 1
#    else
#        define PHI_SUPPORTS_IS_FUNCTION() 0
#    endif

#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_FUNCTION_HPP
