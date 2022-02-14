#ifndef INCG_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_OFFSETOF_HPP
#define INCG_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_OFFSETOF_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#if !defined(PHI_OFFSETOF) && !defined(PHI_SUPPORTS_OFFSETOF)
#    if PHI_HAS_INTRINSIC_BUILTIN_OFFSET_OF()
#        define PHI_OFFSETOF(type, member) __builtin_offsetof(type, member)
#        define PHI_SUPPORTS_OFFSETOF()    1
#    else
#        define PHI_OFFSETOF(type, member) 0
#        define PHI_SUPPORTS_OFFSETOF()    0
#    endif
#endif

#endif // INCG_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_OFFSETOF_HPP
