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

// Define macros for opening and closing the std namespace
#if PHI_STANDARD_LIBRARY_LIBCXX()

// Include <__config> for libc++
// See https://github.com/llvm/llvm-project/blob/main/libcxx/include/__config
#    ifndef _LIBCPP___CONFIG
#        include <__config>
#    endif

#    define DETAIL_PHI_BEGIN_STD_NAMESPACE() _LIBCPP_BEGIN_NAMESPACE_STD
#    define DETAIL_PHI_END_STD_NAMESPACE()   _LIBCPP_END_NAMESPACE_STD

#elif PHI_STANDARD_LIBRARY_LIBSTDCXX()

// Include <bits/c++-config.h> for libstdc++
// See https://github.com/gcc-mirror/gcc/blob/master/libstdc%2B%2B-v3/include/bits/c%2B%2Bconfig
#    ifndef _GLIBCXX_CXX_CONFIG_H
#        include <bits/c++config.h>
#    endif

// clang-format off
#    define DETAIL_PHI_BEGIN_STD_NAMESPACE() namespace std { _GLIBCXX_BEGIN_NAMESPACE_VERSION
#    define DETAIL_PHI_END_STD_NAMESPACE()   _GLIBCXX_END_NAMESPACE_VERSION }
// clang-format on

#elif PHI_STANDARD_LIBRARY_MSVC()

// Include <yvals_core.h> for MSVC-STL
// See https://github.com/microsoft/STL/blob/main/stl/inc/yvals_core.h
#    ifndef _YVALS_CORE_H_
#        include <yvals_core.h>
#    endif

#    define DETAIL_PHI_BEGIN_STD_NAMESPACE() _STD_BEGIN
#    define DETAIL_PHI_END_STD_NAMESPACE()   _STD_END

#endif

#endif // INCG_PHI_COMPILER_SUPPORT_STANDARD_LIBRARY_HPP
