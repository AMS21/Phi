#ifndef INCG_PHI_COMPILER_SUPPORT_STANDARD_LIBRARY_HPP
#define INCG_PHI_COMPILER_SUPPORT_STANDARD_LIBRARY_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

// Check explicit standards first
#if defined(PHI_CONFIG_STDLIB_LIBCXX)
#    define PHI_STANDARD_LIBRARY_LIBCXX() 1
#elif defined(PHI_CONFIG_STDLIB_LIBSTDCXX)
#    define PHI_STANDARD_LIBRARY_LIBSTDCXX() 1
#else
// Check default standard library
#    include "phi/generated/compiler_support/features.hpp"

#    if PHI_DEFAULT_STDLIB_GLIBCXX()
#        define PHI_STANDARD_LIBRARY_LIBSTDCXX() 1
#    elif PHI_DEFAULT_STDLIB_LLVM_LIBCXX()
#        define PHI_STANDARD_LIBRARY_LIBCXX() 1
#    elif PHI_DEFAULT_STDLIB_MSVC_STL()
#        define PHI_STANDARD_LIBRARY_MSVC() 1
#    else
#        error "Unable to determine default standard library"
#    endif
#endif

#if !defined(PHI_STANDARD_LIBRARY_LIBCXX)
#    define PHI_STANDARD_LIBRARY_LIBCXX() 0
#endif

#if !defined(PHI_STANDARD_LIBRARY_LIBSTDCXX)
#    define PHI_STANDARD_LIBRARY_LIBSTDCXX() 0
#endif

#if !defined(PHI_STANDARD_LIBRARY_MSVC)
#    define PHI_STANDARD_LIBRARY_MSVC() 0
#endif

// Standard library name
#if PHI_STANDARD_LIBRARY_LIBCXX()
#    define PHI_STANDARD_LIBRARY_NAME() "libc++"
#elif PHI_STANDARD_LIBRARY_LIBSTDCXX()
#    define PHI_STANDARD_LIBRARY_NAME() "libstdc++"
#elif PHI_STANDARD_LIBRARY_MSVC()
#    define PHI_STANDARD_LIBRARY_NAME() "msvc-stl"
#endif

#endif // INCG_PHI_COMPILER_SUPPORT_STANDARD_LIBRARY_HPP
