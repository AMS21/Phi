#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_POD_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_POD_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"

#if !defined(PHI_IS_POD) && !defined(PHI_SUPPORTS_IS_POD)

#    if PHI_COMPILER_IS_ATLEAST(GCC, 4, 4, 0) || PHI_COMPILER_IS(CLANG_COMPAT) ||                  \
            PHI_COMPILER_IS(MSVC)
#        define PHI_IS_POD(type)      __is_pod(type)
#        define PHI_SUPPORTS_IS_POD() 1
#    else
#        define PHI_SUPPORTS_IS_POD() 0
#    endif

#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_POD_HPP
