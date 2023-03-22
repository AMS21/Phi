#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_ENUM_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_ENUM_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"

#if !defined(PHI_IS_ENUM) && !defined(PHI_SUPPORTS_IS_ENUM)

#    if PHI_COMPILER_IS_ATLEAST(GCC, 4, 4, 0) || PHI_COMPILER_IS(CLANG_COMPAT) ||                  \
            PHI_COMPILER_IS(MSVC)
#        define PHI_IS_ENUM(type)      __is_enum(type)
#        define PHI_SUPPORTS_IS_ENUM() 1
#    else
#        define PHI_SUPPORTS_IS_ENUM() 0
#    endif

#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_ENUM_HPP
