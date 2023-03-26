#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_HAS_UNIQUE_OBJECT_REPRESENTATIONS_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_HAS_UNIQUE_OBJECT_REPRESENTATIONS_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"

#if !defined(PHI_HAS_UNIQUE_OBJECT_REPRESENTATIONS) &&                                             \
        !defined(PHI_SUPPORTS_HAS_UNIQUE_OBJECT_REPRESENTATIONS)

#    if PHI_COMPILER_IS_ATLEAST(GCC, 7, 0, 0) || PHI_COMPILER_IS_ATLEAST(CLANG, 6, 0, 0) ||        \
            PHI_COMPILER_IS(APPLECLANG) || PHI_COMPILER_IS(EMCC) ||                                \
            PHI_COMPILER_IS_ATLEAST(MSVC, 19, 16, 0)
#        define PHI_HAS_UNIQUE_OBJECT_REPRESENTATIONS(obj)       __has_unique_object_representations(obj)
#        define PHI_SUPPORTS_HAS_UNIQUE_OBJECT_REPRESENTATIONS() 1
#    else
#        define PHI_SUPPORTS_HAS_UNIQUE_OBJECT_REPRESENTATIONS() 0
#    endif

#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_HAS_UNIQUE_OBJECT_REPRESENTATIONS_HPP
