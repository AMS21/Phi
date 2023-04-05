#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_CONSTANT_EVALUATED_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_CONSTANT_EVALUATED_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"

#if !defined(PHI_IS_CONSTANT_EVALUATED) && !defined(PHI_SUPPORTS_IS_CONSTANT_EVALUATED)

#    if PHI_COMPILER_IS_ATLEAST(GCC, 9, 0, 0) || PHI_COMPILER_IS_ATLEAST(CLANG, 9, 0, 0) ||        \
            PHI_COMPILER_IS(APPLECLANG) || PHI_COMPILER_IS(EMCC) ||                                \
            PHI_COMPILER_IS_ATLEAST(MSVC, 19, 29, 0)
#        define PHI_IS_CONSTANT_EVALUATED()          __builtin_is_constant_evaluated()
#        define PHI_SUPPORTS_IS_CONSTANT_EVALUATED() 1
#    else
#        define PHI_SUPPORTS_IS_CONSTANT_EVALUATED() 0
#    endif

#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_CONSTANT_EVALUATED_HPP
