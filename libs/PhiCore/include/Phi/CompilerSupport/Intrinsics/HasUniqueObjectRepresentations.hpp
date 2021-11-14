#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_HAS_UNIQUE_OBJECT_REPRESENTATIONS_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_HAS_UNIQUE_OBJECT_REPRESENTATIONS_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Features.hpp"

#if PHI_HAS_INTRINSIC_HAS_UNIQUE_OBJECT_REPRESENTATIONS()
#    define PHI_HAS_UNIQUE_OBJECT_REPRESENTATIONS(obj)       __has_unique_object_representations(obj)
#    define PHI_SUPPORTS_HAS_UNIQUE_OBJECT_REPRESENTATIONS() 1
#else
#    define PHI_HAS_UNIQUE_OBJECT_REPRESENTATIONS(obj)       false
#    define PHI_SUPPORTS_HAS_UNIQUE_OBJECT_REPRESENTATIONS() 0
#endif

#if defined(PHI_CONFIG_NO_INTRINSICS)
#    undef PHI_SUPPORTS_HAS_UNIQUE_OBJECT_REPRESENTATIONS
#    define PHI_SUPPORTS_HAS_UNIQUE_OBJECT_REPRESENTATIONS() 0
#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_HAS_UNIQUE_OBJECT_REPRESENTATIONS_HPP
