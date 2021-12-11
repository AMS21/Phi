#ifndef INCG_PHI_CORE_COMPILER_SUPPORT_EXTENDED_TYPES_HPP
#define INCG_PHI_CORE_COMPILER_SUPPORT_EXTENDED_TYPES_HPP

#include "phi/compiler_support/features.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

// Float16
#if PHI_HAS_EXTENSION_FLOAT16()
#    define PHI_SUPPORTS_FLOAT16() 1
#    define PHI_FLOAT16            _Float16
#elif PHI_HAS_EXTENSION_FP16()
#    define PHI_SUPPORTS_FLOAT16() 1
#    define PHI_FLOAT16            __fp16
#else
#    define PHI_SUPPORTS_FLOAT16() 0
#    define PHI_FLOAT16            /* Missing support */
#endif

// Float128
#if PHI_HAS_EXTENSION_FLOAT128()
#    define PHI_SUPPORTS_FLOAT128() 1
#    define PHI_FLOAT128            __float128
#else
#    define PHI_SUPPORTS_FLOAT128() 0
#    define PHI_FLOAT128            /* Missing support */
#endif

// int128
#if PHI_HAS_EXTENSION_INT128()
#    define PHI_SUPPORTS_INT128() 1
#    define PHI_INT128            __int128
#    define PHI_UINT128           unsigned __int128
#else
#    define PHI_SUPPORTS_INT128() 0
#    define PHI_INT128            /* Missing support */
#    define PHI_UINT128           /* Missing support */
#endif

#endif // INCG_PHI_CORE_COMPILER_SUPPORT_EXTENDED_TYPES_HPP
