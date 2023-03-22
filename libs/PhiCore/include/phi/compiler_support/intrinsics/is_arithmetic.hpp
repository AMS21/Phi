#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_ARITHMETIC_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_ARITHMETIC_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"

#if !defined(PHI_IS_ARITHMETIC) && !defined(PHI_SUPPORTS_IS_ARITHMETIC)

#    if PHI_COMPILER_IS(CLANG_COMPAT)
#        define PHI_IS_ARITHMETIC(type)      __is_arithmetic(type)
#        define PHI_SUPPORTS_IS_ARITHMETIC() 1
#    else
#        define PHI_SUPPORTS_IS_ARITHMETIC() 0
#    endif

#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_ARITHMETIC_HPP
