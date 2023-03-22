#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_UNDERLYING_TYPE_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_UNDERLYING_TYPE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"

#if !defined(PHI_UNDERLYING_TYPE) && !defined(PHI_SUPPORTS_UNDERLYING_TYPE)

#    if PHI_COMPILER_IS_ATLEAST(GCC, 6, 0, 0) || PHI_COMPILER_IS(CLANG_COMPAT) ||                  \
            PHI_COMPILER_IS(MSVC)
#        define PHI_UNDERLYING_TYPE(type)      __underlying_type(type)
#        define PHI_SUPPORTS_UNDERLYING_TYPE() 1
#    else
#        define PHI_SUPPORTS_UNDERLYING_TYPE() 0
#    endif

#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_UNDERLYING_TYPE_HPP
