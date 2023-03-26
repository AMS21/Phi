#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_HAS_TRIVIAL_DESTRUCTOR_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_HAS_TRIVIAL_DESTRUCTOR_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"

#if !defined(PHI_HAS_TRIVIAL_DESTRUCTOR) && !defined(PHI_SUPPORTS_HAS_TRIVIAL_DESTRUCTOR)

#    if PHI_COMPILER_IS_ATLEAST(GCC, 4, 4, 0) || PHI_COMPILER_IS(CLANG_COMPAT) ||                  \
            PHI_COMPILER_IS(MSVC)
#        define PHI_HAS_TRIVIAL_DESTRUCTOR(type)      __has_trivial_destructor(type)
#        define PHI_SUPPORTS_HAS_TRIVIAL_DESTRUCTOR() 1
#    else
#        define PHI_SUPPORTS_HAS_TRIVIAL_DESTRUCTOR() 0
#    endif

#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_HAS_TRIVIAL_DESTRUCTOR_HPP
