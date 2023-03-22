#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_TRIVIALLY_ASSIGNABLE_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_TRIVIALLY_ASSIGNABLE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"

#if !defined(PHI_IS_TRIVIALLY_ASSIGNABLE) && !defined(PHI_SUPPORTS_IS_TRIVIALLY_ASSIGNABLE)

#    if PHI_COMPILER_IS_ATLEAST(GCC, 5, 0, 0) || PHI_COMPILER_IS_ATLEAST(CLANG, 3, 1, 0) ||        \
            PHI_COMPILER_IS(APPLECLANG) || PHI_COMPILER_IS(EMCC) || PHI_COMPILER_IS(MSVC)
#        define PHI_IS_TRIVIALLY_ASSIGNABLE(type, with_type)                                       \
            __is_trivially_assignable(type, with_type)
#        define PHI_SUPPORTS_IS_TRIVIALLY_ASSIGNABLE() 1
#    else
#        define PHI_SUPPORTS_IS_TRIVIALLY_ASSIGNABLE() 0
#    endif

#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_TRIVIALLY_ASSIGNABLE_HPP
