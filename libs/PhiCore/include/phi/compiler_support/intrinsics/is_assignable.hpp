#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_ASSIGNABLE_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_ASSIGNABLE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"

#if !defined(PHI_IS_ASSIGNABLE) && !defined(PHI_SUPPORTS_IS_ASSIGNABLE)

#    if PHI_COMPILER_IS_ATLEAST(GCC, 8, 0, 0) || PHI_COMPILER_IS_ATLEAST(CLANG, 3, 9, 0) ||        \
            PHI_COMPILER_IS(APPLECLANG) || PHI_COMPILER_IS(EMCC) ||                                \
            PHI_COMPILER_IS_ATLEAST(MSVC, 19, 16, 0)
#        define PHI_IS_ASSIGNABLE(type, with_type) __is_assignable(type, with_type)
#        define PHI_SUPPORTS_IS_ASSIGNABLE()       1
#    else
#        define PHI_SUPPORTS_IS_ASSIGNABLE() 0
#    endif
#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_ASSIGNABLE_HPP
