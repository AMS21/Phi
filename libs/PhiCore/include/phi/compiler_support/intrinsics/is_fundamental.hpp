#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_FUNDAMENTAL_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_FUNDAMENTAL_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"

#if !defined(PHI_IS_FUNDAMENTAL) && !defined(PHI_SUPPORTS_IS_FUNDAMENTAL)

#    if PHI_COMPILER_IS(CLANG_COMPAT)
#        define PHI_IS_FUNDAMENTAL(type)      __is_fundamental(type)
#        define PHI_SUPPORTS_IS_FUNDAMENTAL() 1
#    else
#        define PHI_SUPPORTS_IS_FUNDAMENTAL() 0
#    endif

#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_FUNDAMENTAL_HPP
