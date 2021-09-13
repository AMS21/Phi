#ifndef INCG_PHI_CORE_CONFIG_FLATTEN_HPP
#define INCG_PHI_CORE_CONFIG_FLATTEN_HPP

#include "Phi/CompilerSupport/Features.hpp"

#if PHI_HAS_EXTENSION_ATTRIBUTE_FLATTEN()
#    define PHI_FLATTEN __attribute__((flatten))
#else
#    define PHI_FLATTEN /* Nothing */
#endif

#endif // INCG_PHI_CORE_CONFIG_FLATTEN_HPP
