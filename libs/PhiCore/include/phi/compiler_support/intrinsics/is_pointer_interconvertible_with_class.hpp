#ifndef INCG_PHI_CORE_COMPILER_SUPPORTS_INTRINSICS_IS_POINTER_INTERCONVERTIBLE_WITH_CLASS_HPP
#define INCG_PHI_CORE_COMPILER_SUPPORTS_INTRINSICS_IS_POINTER_INTERCONVERTIBLE_WITH_CLASS_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"

#if !defined(PHI_IS_POINTER_INTERCONVERTIBLE_WITH_CLASS) &&                                        \
        !defined(PHI_SUPPORTS_IS_POINTER_INTERCONVERTIBLE_WITH_CLASS)

#    if PHI_COMPILER_IS_ATLEAST(GCC, 12, 0, 0)
#        define PHI_IS_POINTER_INTERCONVERTIBLE_WITH_CLASS(member_pointer)                         \
            __is_pointer_interconvertible_with_class(member_pointer)
#        define PHI_SUPPORTS_IS_POINTER_INTERCONVERTIBLE_WITH_CLASS() 1
#    else
#        define PHI_SUPPORTS_IS_POINTER_INTERCONVERTIBLE_WITH_CLASS() 0
#    endif

#endif

#endif // INCG_PHI_CORE_COMPILER_SUPPORTS_INTRINSICS_IS_POINTER_INTERCONVERTIBLE_WITH_CLASS_HPP
