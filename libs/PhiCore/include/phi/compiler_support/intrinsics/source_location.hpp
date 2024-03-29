#ifndef INCG_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_SOURCE_LOCATION_HPP
#define INCG_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_SOURCE_LOCATION_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"

#if !defined(PHI_SUPPORTS_BUILTIN_LINE)
#    if PHI_COMPILER_IS_ATLEAST(GCC, 4, 8, 0) || PHI_COMPILER_IS_ATLEAST(CLANG, 9, 0, 0) ||        \
            PHI_COMPILER_IS(APPLECLANG) || PHI_COMPILER_IS(EMCC) ||                                \
            PHI_COMPILER_IS_ATLEAST(MSVC, 19, 26, 0)
#        define PHI_SUPPORTS_BUILTIN_LINE()     1
#        define PHI_SUPPORTS_BUILTIN_FILE()     1
#        define PHI_SUPPORTS_BUILTIN_FUNCTION() 1
#    else
#        define PHI_SUPPORTS_BUILTIN_LINE()     0
#        define PHI_SUPPORTS_BUILTIN_FILE()     0
#        define PHI_SUPPORTS_BUILTIN_FUNCTION() 0
#    endif
#endif

#if !defined(PHI_SUPPORTS_BUILTIN_COLUMN)
#    if PHI_COMPILER_IS_ATLEAST(CLANG, 9, 0, 0) || PHI_COMPILER_IS(APPLECLANG) ||                  \
            PHI_COMPILER_IS(EMCC) || PHI_COMPILER_IS_ATLEAST(MSVC, 19, 26, 0)
#        define PHI_SUPPORTS_BUILTIN_COLUMN() 1
#    else
#        define PHI_SUPPORTS_BUILTIN_COLUMN() 0
#    endif
#endif

#endif // INCG_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_SOURCE_LOCATION_HPP
