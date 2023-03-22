#ifndef INCG_PHI_CORE_COMPILER_SUPPORT_UNUSED_HPP
#define INCG_PHI_CORE_COMPILER_SUPPORT_UNUSED_HPP

#include "phi/compiler_support/features.hpp"
#include "phi/generated/compiler_support/features.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#if PHI_HAS_FEATURE_ATTRIBUTE_MAYBE_UNUSED()
#    define PHI_UNUSED [[maybe_unused]]
#elif PHI_HAS_EXTENSION_ATTRIBUTE_UNUSED()
#    define PHI_UNUSED __attribute((unused))
#else
#    define PHI_UNUSED /* Unused */
#endif

#define PHI_UNUSED_PARAMETER(variable) ((void)(variable))
#define PHI_UNUSED_VARIABLE(variable)  ((void)(variable))

#endif // INCG_PHI_CORE_COMPILER_SUPPORT_UNUSED_HPP
