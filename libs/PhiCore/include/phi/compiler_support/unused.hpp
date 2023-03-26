#ifndef INCG_PHI_CORE_COMPILER_SUPPORT_UNUSED_HPP
#define INCG_PHI_CORE_COMPILER_SUPPORT_UNUSED_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"
#include "phi/compiler_support/features.hpp"

#if PHI_HAS_FEATURE_ATTRIBUTE_MAYBE_UNUSED()
#    define PHI_UNUSED [[maybe_unused]]
#elif PHI_COMPILER_IS(GCC) || PHI_COMPILER_IS(CLANG_COMPAT)
#    define PHI_UNUSED __attribute((unused))
#else
#    define PHI_UNUSED /* Unused */
#endif

#define PHI_UNUSED_PARAMETER(variable) ((void)(variable))
#define PHI_UNUSED_VARIABLE(variable)  ((void)(variable))

#endif // INCG_PHI_CORE_COMPILER_SUPPORT_UNUSED_HPP
