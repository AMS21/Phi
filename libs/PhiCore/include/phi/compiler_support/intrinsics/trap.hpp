#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_TRAP_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_TRAP_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"

#if !defined(PHI_TRAP) && !defined(PHI_SUPPORTS_TRAP)

#    if PHI_COMPILER_IS(GCC) || PHI_COMPILER_IS(CLANG_COMPAT)
#        define PHI_TRAP()          __builtin_trap()
#        define PHI_SUPPORTS_TRAP() 1
#    elif PHI_COMPILER_IS(MSVC)
// https://learn.microsoft.com/cpp/intrinsics/fastfail
extern "C" void __fastfail(unsigned int);
#        define PHI_TRAP()          __fastfail(0);
#        define PHI_SUPPORTS_TRAP() 1
#    else
#        define PHI_SUPPORTS_TRAP() 0
#    endif
#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_TRAP_HPP
