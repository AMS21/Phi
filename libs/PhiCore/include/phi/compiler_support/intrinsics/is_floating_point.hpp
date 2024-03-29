#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_FLOATING_POINT_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_FLOATING_POINT_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"

#if !defined(PHI_IS_FLOATING_POINT) && !defined(PHI_SUPPORTS_IS_FLOATING_POINT)

#    if PHI_COMPILER_IS(CLANG_COMPAT)
#        define PHI_IS_FLOATING_POINT(type)      __is_floating_point(type)
#        define PHI_SUPPORTS_IS_FLOATING_POINT() 1
#    else
#        define PHI_SUPPORTS_IS_FLOATING_POINT() 0
#    endif

#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_FLOATING_POINT_HPP
