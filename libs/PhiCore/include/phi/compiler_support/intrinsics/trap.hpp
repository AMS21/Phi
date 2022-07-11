#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_TRAP_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_TRAP_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/generated/compiler_support/features.hpp"

#if !defined(PHI_TRAP) && !defined(PHI_SUPPORTS_TRAP)
#    if PHI_HAS_EXTENSION_BUILTIN_TRAP()
#        define PHI_TRAP()          __builtin_trap()
#        define PHI_SUPPORTS_TRAP() 1
#    elif PHI_HAS_EXTENSION_FASTFAIL()
// https://docs.microsoft.com/en-us/cpp/intrinsics/fastfail
extern "C" void __fastfail(unsigned int);
#        define PHI_TRAP()          __fastfail(0);
#        define PHI_SUPPORTS_TRAP() 1
#    else
#        define PHI_TRAP()          ((void)0)
#        define PHI_SUPPORTS_TRAP() 0
#    endif

#    if defined(PHI_CONFIG_NO_INTRINSICS)
#        undef PHI_SUPPORTS_TRAP
#        define PHI_SUPPORTS_TRAP() 0
#    endif
#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_TRAP_HPP
