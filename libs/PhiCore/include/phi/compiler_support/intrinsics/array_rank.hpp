#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_ARRAY_RANK_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_ARRAY_RANK_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"

#if !defined(PHI_ARRAY_RANK) && !defined(PHI_SUPPORTS_ARRAY_RANK)

#    if PHI_COMPILER_IS(CLANG_COMPAT)
#        define PHI_ARRAY_RANK(type)      __array_rank(type)
#        define PHI_SUPPORTS_ARRAY_RANK() 1
#    else
#        define PHI_SUPPORTS_ARRAY_RANK() 0
#    endif

#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_ARRAY_RANK_HPP
