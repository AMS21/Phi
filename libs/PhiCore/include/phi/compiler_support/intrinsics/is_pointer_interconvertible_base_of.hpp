#ifndef INCG_PHI_CORE_COMPILER_SUPPORTS_INTRINSIC_IS_POINTER_INTERCONVERTIBLE_BASE_OF_HPP
#define INCG_PHI_CORE_COMPILER_SUPPORTS_INTRINSIC_IS_POINTER_INTERCONVERTIBLE_BASE_OF_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"

#if !defined(PHI_IS_POINTER_INTERCONVERTIBLE_BASE_OF) &&                                           \
        !defined(PHI_SUPPORTS_IS_POINTER_INTERCONVERTIBLE_BASE_OF)

#    if PHI_COMPILER_IS_ATLEAST(GCC, 12, 0, 0) || PHI_COMPILER_IS_ATLEAST(MSVC, 19, 29, 0)
#        define PHI_IS_POINTER_INTERCONVERTIBLE_BASE_OF(base, derived)                             \
            __is_pointer_interconvertible_base_of(base, derived)
#        define PHI_SUPPORTS_IS_POINTER_INTERCONVERTIBLE_BASE_OF() 1
#    else
#        define PHI_SUPPORTS_IS_POINTER_INTERCONVERTIBLE_BASE_OF() 0
#    endif

#endif

#endif // INCG_PHI_CORE_COMPILER_SUPPORTS_INTRINSIC_IS_POINTER_INTERCONVERTIBLE_BASE_OF_HPP
