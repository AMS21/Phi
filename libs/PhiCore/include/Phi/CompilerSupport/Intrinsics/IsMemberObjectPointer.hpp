#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_MEMBER_OBJECT_POINTER_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_MEMBER_OBJECT_POINTER_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Features.hpp"

#if PHI_HAS_INTRINSIC_IS_MEMBER_OBJECT_POINTER()
#    define PHI_IS_MEMBER_OBJECT_POINTER(type)      __is_member_object_pointer(type)
#    define PHI_SUPPORTS_IS_MEMBER_OBJECT_POINTER() 1
#else
#    define PHI_IS_MEMBER_OBJECT_POINTER(type)      false
#    define PHI_SUPPORTS_IS_MEMBER_OBJECT_POINTER() 0
#endif

#if defined(PHI_CONFIG_NO_INTRINSICS)
#    undef PHI_SUPPORTS_IS_MEMBER_OBJECT_POINTER
#    define PHI_SUPPORTS_IS_MEMBER_OBJECT_POINTER() 0
#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_MEMBER_OBJECT_POINTER_HPP
