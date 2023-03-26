#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_REMOVE_CV_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_REMOVE_CV_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"

#if !defined(PHI_REMOVE_CV) && !defined(PHI_SUPPORTS_REMOVE_CV)

#    if PHI_COMPILER_IS_ATLEAST(CLANG, 16, 0, 0)
#        define PHI_REMOVE_CV(type)      __remove_cv(type)
#        define PHI_SUPPORTS_REMOVE_CV() 1
#    else
#        define PHI_SUPPORTS_REMOVE_CV() 0
#    endif

#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_REMOVE_CV_HPP
