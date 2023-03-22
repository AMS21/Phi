#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_ABSTRACT_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_ABSTRACT_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/generated/compiler_support/features.hpp"

#if !defined(PHI_IS_ABSTRACT) && !defined(PHI_SUPPORTS_IS_ABSTRACT)

#    if PHI_COMPILER_IS_ATLEAST(GCC, 4, 4, 0) || PHI_COMPILER_IS(CLANG_COMPAT) ||                  \
            PHI_COMPILER_IS(MSVC)
#        define PHI_IS_ABSTRACT(type)      __is_abstract(type)
#        define PHI_SUPPORTS_IS_ABSTRACT() 1
#    else
#        define PHI_SUPPORTS_IS_ABSTRACT() 0
#    endif

#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_ABSTRACT_HPP
