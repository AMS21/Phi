#ifndef INCG_PHI_CONFIG_CPLUSPLUS_HPP
#define INCG_PHI_CONFIG_CPLUSPLUS_HPP

#include "Phi/Config/Compiler.hpp"

// C++-98 standard from november 1997
#define PHI_CPLUSPLUS_98() (199711L)
// C++-11 standard from march 2011
#define PHI_CPLUSPLUS_11() (201103L)
// C++-14 standard from february 2014
#define PHI_CPLUSPLUS_14() (201402L)
// C++-17 standard from march 2017
#define PHI_CPLUSPLUS_17() (201703L)
// C++-20 standard from feburary 2020
#define PHI_CPLUSPLUS_20() (202002L)
// C++-23 standard (Working draft)
#define PHI_CPLUSPLUS_23() (202101L)
// Latest C++ standard
#define PHI_CPLUSPLUS_LATEST() PHI_CPLUSPLUS_23()

#if PHI_COMPILER_IS(MSVC)
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

#endif // INCG_PHI_CONFIG_CPLUSPLUS_HPP
