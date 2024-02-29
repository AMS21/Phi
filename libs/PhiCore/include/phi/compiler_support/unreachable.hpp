#ifndef INCG_PHI_CORE_COMPILER_SUPPORT_UNREACHABLE_HPP
#define INCG_PHI_CORE_COMPILER_SUPPORT_UNREACHABLE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"

#if PHI_COMPILER_IS_ATLEAST(GCC, 4, 5, 0) || PHI_COMPILER_IS(CLANG_COMPAT)

#    define PHI_UNREACHABLE() __builtin_unreachable()

#elif PHI_COMPILER_IS(MSVC)

#    define PHI_UNREACHABLE() __assume(0)

#else

#    define PHI_UNREACHABLE() ((void)0)

#endif

#endif // INCG_PHI_CORE_COMPILER_SUPPORT_UNREACHABLE_HPP
