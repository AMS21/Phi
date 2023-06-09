#ifndef INCG_PHI_COMPILER_SUPPORT_STANDARD_LIBRARY_HPP
#define INCG_PHI_COMPILER_SUPPORT_STANDARD_LIBRARY_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include <phi/generated/compiler_support/libraries.hpp>

// Check if the standard library has the <version> header
#if PHI_HAS_LIB_VERSION()

// Since C++-20 the <version> header should be used instead of <ciso646> to detect the standard library.
// Also the <ciso646> header was removed with C++-20.
// See: https://en.cppreference.com/w/cpp/header/version
// See: https://en.cppreference.com/w/cpp/header/ciso646
#    include <version>

#else

// Otherwise include ciso646 as it usually includes the standard library specific headers
#    include <ciso646>

#endif

// Check explicit standards first
#if defined(PHI_CONFIG_STDLIB_LIBCXX)
#    define PHI_STANDARD_LIBRARY_LIBCXX() 1
#elif defined(PHI_CONFIG_STDLIB_LIBSTDCXX)
#    define PHI_STANDARD_LIBRARY_LIBSTDCXX() 1
#else
// Check default standard library

#    if defined(__GLIBCXX__)
#        define PHI_STANDARD_LIBRARY_LIBSTDCXX() 1
#    elif defined(_LIBCPP_VERSION)
#        define PHI_STANDARD_LIBRARY_LIBCXX() 1
#    elif defined(_MSVC_STL_VERSION)
#        define PHI_STANDARD_LIBRARY_MSVC() 1
#    else
#        error "Unable to determine default standard library"
#    endif
#endif

#if !defined(PHI_STANDARD_LIBRARY_LIBSTDCXX)
#    define PHI_STANDARD_LIBRARY_LIBSTDCXX() 0
#endif

#if !defined(PHI_STANDARD_LIBRARY_LIBCXX)
#    define PHI_STANDARD_LIBRARY_LIBCXX() 0
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

// Define macros for opening and closing the std namespace
#if PHI_STANDARD_LIBRARY_LIBCXX()

// See https://github.com/llvm/llvm-project/blob/main/libcxx/include/ciso646
// https://github.com/llvm/llvm-project/blob/main/libcxx/include/__config

#    define DETAIL_PHI_BEGIN_STD_NAMESPACE() _LIBCPP_BEGIN_NAMESPACE_STD
#    define DETAIL_PHI_END_STD_NAMESPACE()   _LIBCPP_END_NAMESPACE_STD

#elif PHI_STANDARD_LIBRARY_LIBSTDCXX()

// See https://github.com/gcc-mirror/gcc/blob/master/libstdc%2B%2B-v3/include/c/ciso646
// https://github.com/gcc-mirror/gcc/blob/master/libstdc%2B%2B-v3/include/bits/c%2B%2Bconfig

// clang-format off
#    define DETAIL_PHI_BEGIN_STD_NAMESPACE() namespace std { _GLIBCXX_BEGIN_NAMESPACE_VERSION
#    define DETAIL_PHI_END_STD_NAMESPACE()   _GLIBCXX_END_NAMESPACE_VERSION }
// clang-format on

#elif PHI_STANDARD_LIBRARY_MSVC()

// See https://github.com/microsoft/STL/blob/main/stl/inc/ciso646
// https://github.com/microsoft/STL/blob/main/stl/inc/yvals_core.h

#    define DETAIL_PHI_BEGIN_STD_NAMESPACE() _STD_BEGIN
#    define DETAIL_PHI_END_STD_NAMESPACE()   _STD_END

#endif

#endif // INCG_PHI_COMPILER_SUPPORT_STANDARD_LIBRARY_HPP
