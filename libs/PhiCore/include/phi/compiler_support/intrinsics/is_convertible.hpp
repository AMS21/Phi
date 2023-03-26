#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_CONVERTIBLE_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_CONVERTIBLE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"

#if !defined(PHI_IS_CONVERTIBLE) && !defined(PHI_SUPPORTS_IS_CONVERTIBLE)

#    if PHI_COMPILER_IS(CLANG_COMPAT)
#        define PHI_IS_CONVERTIBLE(from, to)  __is_convertible(from, to)
#        define PHI_SUPPORTS_IS_CONVERTIBLE() 1
#    elif PHI_COMPILER_IS(MSVC)
// NOTE: Clang also support __is_convertible_to
#        define PHI_IS_CONVERTIBLE(from, to)  __is_convertible_to(from, to)
#        define PHI_SUPPORTS_IS_CONVERTIBLE() 1
#    else
#        define PHI_SUPPORTS_IS_CONVERTIBLE() 0
#    endif

#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_CONVERTIBLE_HPP
