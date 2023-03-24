#ifndef INCG_PHI_CORE_COMPILER_SUPPORT_ASSUME_HPP
#define INCG_PHI_CORE_COMPILER_SUPPORT_ASSUME_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"

#if PHI_COMPILER_IS_ATLEAST(GCC, 4, 5, 0)
// clang-format off
#    define PHI_ASSUME(condition) if (condition){} else __builtin_unreachable()
// clang-format on
#elif PHI_COMPILER_IS_ATLEAST(CLANG, 3, 6, 0) || PHI_COMPILER_IS(APPLECLANG) ||                    \
        PHI_COMPILER_IS(EMCC)
#    define PHI_ASSUME(condition) __builtin_assume(condition)
#elif PHI_COMPILER_IS(MSVC)
#    define PHI_ASSUME(condition) __assume(condition)
#else
#    define PHI_ASSUME(condition) ((void)0)
#endif

#endif // INCG_PHI_CORE_COMPILER_SUPPORT_ASSUME_HPP
