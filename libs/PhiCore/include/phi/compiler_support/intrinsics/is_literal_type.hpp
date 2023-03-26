#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_LITERAL_TYPE_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_LITERAL_TYPE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"

#if !defined(PHI_IS_LITERAL_TYPE) && !defined(PHI_SUPPORTS_IS_LITERAL_TYPE)

#    if PHI_COMPILER_IS_ATLEAST(GCC, 4, 6, 0) || PHI_COMPILER_IS(CLANG_COMPAT) ||                  \
            PHI_COMPILER_IS(MSVC)
#        define PHI_IS_LITERAL_TYPE(type)      __is_literal_type(type)
#        define PHI_SUPPORTS_IS_LITERAL_TYPE() 1
#    else
#        define PHI_SUPPORTS_IS_LITERAL_TYPE() 0
#    endif

#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_LITERAL_TYPE_HPP
