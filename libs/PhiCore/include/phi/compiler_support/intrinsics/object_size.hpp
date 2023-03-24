#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_OBJECT_SIZE_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_OBJECT_SIZE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"

#if !defined(PHI_OBJECT_SIZE) && !defined(PHI_SUPPORTS_OBJECT_SIZE)

// https://gcc.gnu.org/onlinedocs/gcc/Object-Size-Checking.html
// https://clang.llvm.org/docs/LanguageExtensions.html#evaluating-object-size-dynamically

#    if PHI_COMPILER_IS(GCC) || PHI_COMPILER_IS(CLANG_COMPAT)
#        define PHI_OBJECT_SIZE(pointer, type) __builtin_object_size(pointer, type)
#        define PHI_SUPPORTS_OBJECT_SIZE()     1
#    else
#        define PHI_SUPPORTS_OBJECT_SIZE() 0
#    endif

#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_OBJECT_SIZE_HPP
