#ifndef INCG_PHI_CORE_COMPILER_SUPPORT_IS_NAN_HPP
#define INCG_PHI_CORE_COMPILER_SUPPORT_IS_NAN_HPP

#include "phi/generated/compiler_support/features.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#if PHI_HAS_INTRINSIC_BUILTIN_ISNAN()
#    define PHI_IS_NAN(value) __builtin_isnan(value)
#else
#    define PHI_IS_NAN(value) (value != value)
#endif

#endif // INCG_PHI_CORE_COMPILER_SUPPORT_IS_NAN_HPP
