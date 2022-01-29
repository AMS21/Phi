#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_POLYMORPHIC_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_POLYMORPHIC_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/generated/compiler_support/features.hpp"

#if PHI_HAS_INTRINSIC_IS_POLYMORPHIC()
#    define PHI_IS_POLYMORPHIC(type)      __is_polymorphic(type)
#    define PHI_SUPPORTS_IS_POLYMORPHIC() 1
#else
#    define PHI_IS_POLYMORPHIC(type)      false
#    define PHI_SUPPORTS_IS_POLYMORPHIC() 0
#endif

#if defined(PHI_CONFIG_NO_INTRINSICS)
#    undef PHI_SUPPORTS_IS_POLYMORPHIC
#    define PHI_SUPPORTS_IS_POLYMORPHIC() 0
#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_POLYMORPHIC_HPP
