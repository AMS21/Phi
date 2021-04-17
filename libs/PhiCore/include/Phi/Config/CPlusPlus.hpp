#pragma once

#include "Phi/PhiConfig.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

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

#define PHI_CPP_STANDARD_IS_EXACTLY(standard) (__cplusplus == PHI_CPLUSPLUS_##standard())

#define PHI_CPP_STANDARD_IS_ATLEAST(standard) (__cplusplus >= PHI_CPLUSPLUS_##standard())

#define PHI_CPP_STANDARD_IS_BELOW(standard) (__cplusplus < PHI_CPLUSPLUS_##standard())

DETAIL_PHI_END_NAMESPACE()
