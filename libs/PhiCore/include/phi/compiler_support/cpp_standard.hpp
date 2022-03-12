#ifndef INCG_PHI_CORE_COMPILER_SUPPORT_CPLUSPLUS_HPP
#define INCG_PHI_CORE_COMPILER_SUPPORT_CPLUSPLUS_HPP

#include "phi/compiler_support/compiler.hpp"

// C++-98 standard from november 1997
#define PHI_CPLUSPLUS_98() (199711L)

// C++-11 standard from march 2011
#define PHI_CPLUSPLUS_11() (201103L)

// C++-14 standard from february 2014
#define PHI_CPLUSPLUS_14() (201402L)

// C++-17 standard from march 2017
#define PHI_CPLUSPLUS_17() (201703L)

// C++-20
#if PHI_COMPILER_IS_BELOW(GCC, 11, 0, 0)
// GCC-8 - GCC-10 use 201709 for C++-20
// See: https://godbolt.org/z/86a93zjYo
#    define PHI_CPLUSPLUS_20() (201709L)
#elif PHI_COMPILER_IS_BELOW(CLANG, 10, 0, 0) || PHI_COMPILER_IS_BELOW(EMCC, 1, 39, 0) ||           \
        PHI_COMPILER_IS(APPLECLANG)
// Clang version before clang-10 uses 201707 for C++-20
#    define PHI_CPLUSPLUS_20() (201707L)
#else
// C++-20 standard from feburary 2020
#    define PHI_CPLUSPLUS_20() (202002L)
#endif

// C++-23
#if PHI_COMPILER_IS(GCC)
#    define PHI_CPLUSPLUS_23() (202100L)
#elif PHI_COMPILER_IS(MSVC) && PHI_COMPILER_IS_NOT(WINCLANG)
#    define PHI_CPLUSPLUS_23() (202004L)
#else
// C++-23 standard (Working draft)
#    define PHI_CPLUSPLUS_23() (202101L)
#endif

// Latest C++ standard
#define PHI_CPLUSPLUS_LATEST() PHI_CPLUSPLUS_23()

#if PHI_COMPILER_IS(MSVC) && PHI_COMPILER_IS_NOT(WINCLANG)
#    if defined(_MSVC_LANG)
#        define PHI_CPP_STANDARD() _MSVC_LANG
#    else
#        define PHI_CPP_STANDARD() PHI_CPLUSPLUS_LATEST()
#    endif
#elif defined(__cplusplus)
#    define PHI_CPP_STANDARD() __cplusplus
#else
// Use C++-98 as fallback
#    define PHI_CPP_STANDARD() PHI_CPLUSPLUS_98()
#endif

#define PHI_CPP_STANDARD_IS_EXACTLY(standard) (PHI_CPP_STANDARD() == PHI_CPLUSPLUS_##standard())

#define PHI_CPP_STANDARD_IS_GREATER(standard) (PHI_CPP_STANDARD() > PHI_CPLUSPLUS_##standard())

#define PHI_CPP_STANDARD_IS_ATLEAST(standard) (PHI_CPP_STANDARD() >= PHI_CPLUSPLUS_##standard())

#define PHI_CPP_STANDARD_IS_BELOW(standard) (PHI_CPP_STANDARD() < PHI_CPLUSPLUS_##standard())

#if PHI_CPP_STANDARD_IS_EXACTLY(23)
#    define PHI_CPP_STANDARD_SHORT() 23
#elif PHI_CPP_STANDARD_IS_EXACTLY(20)
#    define PHI_CPP_STANDARD_SHORT() 20
#elif PHI_CPP_STANDARD_IS_EXACTLY(17)
#    define PHI_CPP_STANDARD_SHORT() 17
#elif PHI_CPP_STANDARD_IS_EXACTLY(14)
#    define PHI_CPP_STANDARD_SHORT() 14
#elif PHI_CPP_STANDARD_IS_EXACTLY(11)
#    define PHI_CPP_STANDARD_SHORT() 11
#else
// C++-98 as fallback
#    define PHI_CPP_STANDARD_SHORT() 98
#endif

#endif // INCG_PHI_CORE_COMPILER_SUPPORT_CPLUSPLUS_HPP
