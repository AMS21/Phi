#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_ADDRESS_OF_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_ADDRESS_OF_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"

#if !defined(PHI_ADDRESS_OF) && !defined(PHI_SUPPORTS_ADDRESS_OF)

#    if PHI_COMPILER_IS_ATLEAST(GCC, 7, 0, 0) || PHI_COMPILER_IS_ATLEAST(CLANG, 3, 4, 0) ||        \
            PHI_COMPILER_IS(EMCC) || PHI_COMPILER_IS(APPLECLANG) ||                                \
            PHI_COMPILER_IS_ATLEAST(MSVC, 19, 16, 0)
#        define PHI_ADDRESS_OF(obj)       __builtin_addressof(obj)
#        define PHI_SUPPORTS_ADDRESS_OF() 1
#    else
#        define PHI_SUPPORTS_ADDRESS_OF() 0
#    endif

#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_ADDRESS_OF_HPP
