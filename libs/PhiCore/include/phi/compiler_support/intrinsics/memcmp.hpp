#ifndef INCG_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_MEMCMP_HPP
#define INCG_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_MEMCMP_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"

#if PHI_COMPILER_IS(GCC) || PHI_COMPILER_IS(CLANG_COMPAT) ||                                       \
        PHI_COMPILER_IS_ATLEAST(MSVC, 19, 28, 0)
#    define PHI_MEMCMP(lhs, rhs, count) __builtin_memcmp(lhs, rhs, count)
#    define PHI_SUPPORTS_MEMCMP()       1
#    if PHI_COMPILER_IS_ATLEAST(CLANG, 4, 0, 0) || PHI_COMPILER_IS(APPLECLANG) ||                  \
            PHI_COMPILER_IS(EMCC) || PHI_COMPILER_IS(MSVC)
#        define PHI_SUPPORTS_MEMCMP_CONSTEXPR() 1
#    else
#        define PHI_SUPPORTS_MEMCMP_CONSTEXPR() 0
#    endif
#else
#    define PHI_MEMCMP(lhs, rhs, count)     /* Nothing */
#    define PHI_SUPPORTS_MEMCMP()           0
#    define PHI_SUPPORTS_MEMCMP_CONSTEXPR() 0
#endif

#endif // INCG_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_MEMCMP_HPP
