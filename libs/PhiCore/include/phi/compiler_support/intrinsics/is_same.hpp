#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_SAME_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_SAME_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"

#if !defined(PHI_IS_SAME) && !defined(PHI_SUPPORTS_IS_SAME)

#    if PHI_COMPILER_IS_ATLEAST(GCC, 10, 0, 0) || PHI_COMPILER_IS(CLANG_COMPAT)
#        define PHI_IS_SAME(lhs, rhs)  __is_same(lhs, rhs)
#        define PHI_SUPPORTS_IS_SAME() 1
#    else
#        define PHI_SUPPORTS_IS_SAME() 0
#    endif

#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_SAME_HPP
