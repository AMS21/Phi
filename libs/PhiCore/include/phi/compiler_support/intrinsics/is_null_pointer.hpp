#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_NULLPTR_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_NULLPTR_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"

#if !defined(PHI_IS_NULL_POINTER) && !defined(PHI_SUPPORTS_IS_NULL_POINTER)

// NOTE: __is_nullptr was introduced in Clang 16.0.0, but deprecated in Clang 19.1.0 and removed with Clang 20.1.0.
// See release notes
// Clang: 19.1.0: https://releases.llvm.org/19.1.0/tools/clang/docs/ReleaseNotes.html#non-comprehensive-list-of-changes-in-this-release
// Clang: 20.1.0: https://releases.llvm.org/20.1.0/tools/clang/docs/ReleaseNotes.html#c-specific-potentially-breaking-changes
#    if PHI_COMPILER_IS_ATLEAST(CLANG, 16, 0, 0) && PHI_COMPILER_IS_BELOW(CLANG, 20, 0, 0)
#        define PHI_IS_NULL_POINTER(type)      __is_nullptr(type)
#        define PHI_SUPPORTS_IS_NULL_POINTER() 1
#    else
#        define PHI_SUPPORTS_IS_NULL_POINTER() 0
#    endif

#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_NULLPTR_HPP
