#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_TRIVIAL_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_TRIVIAL_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"

#if !defined(PHI_IS_TRIVIAL) && !defined(PHI_SUPPORTS_IS_TRIVIAL)

#    if PHI_COMPILER_IS_ATLEAST(GCC, 4, 5, 0) || PHI_COMPILER_IS(CLANG_COMPAT) ||                  \
            PHI_COMPILER_IS(MSVC)
#        define PHI_IS_TRIVIAL(type)      __is_trivial(type)
#        define PHI_SUPPORTS_IS_TRIVIAL() 1
#    else
#        define PHI_SUPPORTS_IS_TRIVIAL() 0
#    endif

#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_TRIVIAL_HPP
