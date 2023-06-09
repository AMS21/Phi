#ifndef INCG_PHI_COMPILER_SUPPORT_STANDARD_LIBRARY_HPP
#define INCG_PHI_COMPILER_SUPPORT_STANDARD_LIBRARY_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include <phi/generated/compiler_support/libraries.hpp>
#include <phi/preprocessor/versioning.hpp>

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

#define PHI_STANDARD_LIBRARY_LIBCXX()    0
#define PHI_STANDARD_LIBRARY_LIBSTDCXX() 0
#define PHI_STANDARD_LIBRARY_MSVC()      0

// Check default standard library
#if defined(_LIBCPP_VERSION)

#    undef PHI_STANDARD_LIBRARY_LIBCXX
#    define PHI_STANDARD_LIBRARY_LIBCXX() 1
#    define PHI_STANDARD_LIBRARY_NAME()   "libc++"

// NOTE: libc++ does not provide a date
#    define PHI_STANDARD_LIBRARY_DATE() (0)

#    define PHI_STANDARD_LIBRARY_VERSION_MAJOR() (_LIBCPP_VERSION >> 4)
#    define PHI_STANDARD_LIBRARY_VERSION_MINOR() (_LIBCPP_VERSION >> 2 & 0xFF)
#    define PHI_STANDARD_LIBRARY_VERSION_PATCH() (_LIBCPP_VERSION & 0xFF)

#elif defined(__GLIBCXX__) || defined(_GLIBCXX_RELEASE)

#    undef PHI_STANDARD_LIBRARY_LIBSTDCXX
#    define PHI_STANDARD_LIBRARY_LIBSTDCXX() 1
#    define PHI_STANDARD_LIBRARY_NAME()      "libstdc++"

// Date format: YYYYMMDD
#    define PHI_STANDARD_LIBRARY_DATE()      (__GLIBCXX__)

// NOTE: Not all version of libstdc++ provide the _GLIBCXX_RELEASE macro and it only contains the major version
#    if defined(_GLIBCXX_RELEASE)
#        define PHI_STANDARD_LIBRARY_VERSION_MAJOR() (_GLIBCXX_RELEASE)
#        define PHI_STANDARD_LIBRARY_VERSION_MINOR() (0)
#        define PHI_STANDARD_LIBRARY_VERSION_PATCH() (0)
#    else
#        define PHI_STANDARD_LIBRARY_VERSION_MAJOR() (0)
#        define PHI_STANDARD_LIBRARY_VERSION_MINOR() (0)
#        define PHI_STANDARD_LIBRARY_VERSION_PATCH() (0)
#    endif

#elif defined(_CPPLIB_VER) || defined(_MSVC_STL_VERSION) || defined(_MSVC_STL_UPDATE)

#    undef PHI_STANDARD_LIBRARY_MSVC
#    define PHI_STANDARD_LIBRARY_MSVC() 1
#    define PHI_STANDARD_LIBRARY_NAME() "msvc-stl"

// NOTE: The _MSVC_STL_UPDATE macro was added with Visual Studio 2017 15.5
// See: https://github.com/microsoft/STL/wiki/Macro-_MSVC_STL_UPDATE
#    if defined(_MSVC_STL_UPDATE)

// Date format: YYYYMM
#        define PHI_STANDARD_LIBRARY_DATE() (_MSVC_STL_UPDATE)

#    else

#        define PHI_STANDARD_LIBRARY_DATE() (0)

#    endif

// NOTE: The version seems to match the msvc version output (PHI_MSVC_VERSION not _MSC_VER) but without the patch part
//       See Environment.cmake for more about the MSVC/VS version madness.
#    define PHI_STANDARD_LIBRARY_VERSION_MAJOR() (_MSVC_STL_VERSION / 10)
#    define PHI_STANDARD_LIBRARY_VERSION_MINOR() (_MSVC_STL_VERSION % 10)
#    define PHI_STANDARD_LIBRARY_VERSION_PATCH() (0)

#else

// Probably unsupported standard library used
#    error "Unable to determine default standard library"

#endif

#if PHI_STANDARD_LIBRARY_DATE() > 0
#    define PHI_STANDARD_LIBRARY_HAS_DATE() 1
#else
#    define PHI_STANDARD_LIBRARY_HAS_DATE() 0
#endif

#define PHI_STANDARD_LIBRARY_VERSION()                                                             \
    PHI_VERSION_CREATE(PHI_STANDARD_LIBRARY_VERSION_MAJOR(), PHI_STANDARD_LIBRARY_VERSION_MINOR(), \
                       PHI_STANDARD_LIBRARY_VERSION_PATCH())

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
