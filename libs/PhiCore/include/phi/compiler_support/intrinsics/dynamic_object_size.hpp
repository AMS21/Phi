#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_DYNAMIC_OBJECT_SIZE_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_DYNAMIC_OBJECT_SIZE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"

#if !defined(PHI_DYNAMIC_OBJECT_SIZE) && !defined(PHI_SUPPORTS_OBJECT_SIZE)

// https://gcc.gnu.org/onlinedocs/gcc/Object-Size-Checking.html
// https://clang.llvm.org/docs/LanguageExtensions.html#evaluating-object-size-dynamically

#    if PHI_COMPILER_IS_ATLEAST(GCC, 12, 0, 0) || PHI_COMPILER_IS_ATLEAST(CLANG, 9, 0, 0) ||       \
            PHI_COMPILER_IS(APPLECLANG) || PHI_COMPILER_IS(EMCC)
#        define PHI_DYNAMIC_OBJECT_SIZE(pointer, type) __builtin_dynamic_object_size(pointer, type)
#        define PHI_SUPPORTS_DYNAMIC_OBJECT_SIZE()     1
#    else
#        define PHI_SUPPORTS_DYNAMIC_OBJECT_SIZE() 0
#    endif

#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_DYNAMIC_OBJECT_SIZE_HPP
