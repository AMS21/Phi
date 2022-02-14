#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_LITERAL_TYPE_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_LITERAL_TYPE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/generated/compiler_support/features.hpp"

#if !defined(PHI_IS_LITERAL_TYPE) && !defined(PHI_SUPPORTS_IS_LITERAL_TYPE)
#    if PHI_HAS_INTRINSIC_IS_LITERAL_TYPE()
#        define PHI_IS_LITERAL_TYPE(type)      __is_literal_type(type)
#        define PHI_SUPPORTS_IS_LITERAL_TYPE() 1
#    elif PHI_HAS_INTRINSIC_IS_LITERAL()
PHI_IS_LITERAL_TYPE(type) __is_literal(type)
#        define PHI_SUPPORTS_IS_LITERAL_TYPE() 1
#    else
#        define PHI_IS_LITERAL_TYPE(type)      false
#        define PHI_SUPPORTS_IS_LITERAL_TYPE() 0
#    endif

#    if defined(PHI_CONFIG_NO_INTRINSICS)
#        undef PHI_SUPPORTS_IS_LITERAL_TYPE
#        define PHI_SUPPORTS_IS_LITERAL_TYPE() 0
#    endif
#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_LITERAL_TYPE_HPP
