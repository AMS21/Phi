#ifndef INCG_PHI_CORE_CONFIG_FLATTEN_HPP
#define INCG_PHI_CORE_CONFIG_FLATTEN_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"

#if PHI_COMPILER_IS(GCC) || PHI_COMPILER_IS_ATLEAST(CLANG, 3, 5, 0) ||                             \
        PHI_COMPILER_IS(APPLECLANG) || PHI_COMPILER_IS(EMCC)

#    define PHI_FLATTEN __attribute__((flatten))

#else

#    define PHI_FLATTEN /* Nothing */

#endif

#endif // INCG_PHI_CORE_CONFIG_FLATTEN_HPP
