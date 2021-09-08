#ifndef INCG_PHI_CORE_CONFIG_FLATTEN_HPP
#define INCG_PHI_CORE_CONFIG_FLATTEN_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/Config/Compiler.hpp"

#if PHI_COMPILER_IS(GCC) || PHI_COMPILER_IS_ATLEAST(CLANG, 3, 5, 0)
#    define PHI_FLATTEN __attribute__((flatten))
#else
#    define PHI_FLATTEN /* Nothing */
#endif

#endif // INCG_PHI_CORE_CONFIG_FLATTEN_HPP
