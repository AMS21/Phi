#ifndef INCG_PHI_COMPILER_SUPPORT_LIBRARIES_HPP
#define INCG_PHI_COMPILER_SUPPORT_LIBRARIES_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/cpp_standard.hpp"
#include "phi/compiler_support/standard_library.hpp"
#include "phi/generated/compiler_support/libraries.hpp"

// -- C++-17 --

// string_view
#if PHI_HAS_LIB_STRING_VIEW() && (PHI_STANDARD_LIBRARY_LIBCXX() ||                                 \
                                  (PHI_STANDARD_LIBRARY_LIBSTDCXX() && __cplusplus >= 201703L) ||  \
                                  (PHI_STANDARD_LIBRARY_MSVC() && _HAS_CXX17))
#    define PHI_SUPPORTS_STDLIB_STRING_VIEW() 1
#else
#    define PHI_SUPPORTS_STDLIB_STRING_VIEW() 0
#endif

// -- C++-20 --

// span
#if PHI_HAS_LIB_SPAN() && ((PHI_STANDARD_LIBRARY_LIBCXX() && _LIBCPP_STD_VER >= 20) ||             \
                           (PHI_STANDARD_LIBRARY_LIBSTDCXX() && __cplusplus > 201703L) ||          \
                           (PHI_STANDARD_LIBRARY_MSVC() && _HAS_CXX20))
#    define PHI_SUPPORTS_STDLIB_SPAN() 1
#else
#    define PHI_SUPPORTS_STDLIB_SPAN() 0
#endif

// version
#define PHI_SUPPORTS_STDLIB_VERSION() PHI_HAS_LIB_VERSION()

#endif // INCG_PHI_COMPILER_SUPPORT_LIBRARIES_HPP
