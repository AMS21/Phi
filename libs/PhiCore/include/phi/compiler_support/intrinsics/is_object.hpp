#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_OBJECT_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_OBJECT_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"

#if !defined(PHI_IS_OBJECT) && !defined(PHI_SUPPORTS_IS_OBJECT)

#    if PHI_COMPILER_IS(CLANG_COMPAT)
#        define PHI_IS_OBJECT(type)      __is_object(type)
#        define PHI_SUPPORTS_IS_OBJECT() 1
#    else
#        define PHI_SUPPORTS_IS_OBJECT() 0
#    endif

#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_OBJECT_HPP
