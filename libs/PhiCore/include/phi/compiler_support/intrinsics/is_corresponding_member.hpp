#ifndef INCG_PHIC_CORE_COMPILER_SUPPORT_INTRINSICS_IS_CORRESPONDING_MEMBER_HPP
#define INCG_PHIC_CORE_COMPILER_SUPPORT_INTRINSICS_IS_CORRESPONDING_MEMBER_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#if !defined(PHI_IS_CORRESPONDING_MEMBER) && !defined(PHI_SUPPORTS_IS_CORRESPONDING_MEMBER)
#    if PHI_HAS_INTRINSIC_IS_CORRESPONDING_MEMBER()
#        define PHI_IS_CORRESPONDING_MEMBER(member_lhs, member_rhs)                                \
            __builtin_is_corresponding_member(member_lhs, member_rhs)
#        define PHI_SUPPORTS_IS_CORRESPONDING_MEMBER() 1
#    else
#        define PHI_SUPPORTS_IS_CORRESPONDING_MEMBER() 0
#    endif

#    if defined(PHI_CONFIG_NO_INTRINSICS)
#        undef PHI_SUPPORTS_IS_CORRESPONDING_MEMBER
#        define PHI_SUPPORTS_IS_CORRESPONDING_MEMBER() 0
#    endif
#endif

#endif // INCG_PHIC_CORE_COMPILER_SUPPORT_INTRINSICS_IS_CORRESPONDING_MEMBER_HPP
