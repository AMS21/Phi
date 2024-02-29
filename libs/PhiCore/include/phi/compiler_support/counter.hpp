#ifndef INCG_PHI_CORE_COMPILER_SUPPORT_COUNTER_HPP
#define INCG_PHI_CORE_COMPILER_SUPPORT_COUNTER_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"

#if PHI_COMPILER_IS_ATLEAST(GCC, 4, 4, 0) || PHI_COMPILER_IS(CLANG_COMPAT) || PHI_COMPILER_IS(MSVC)

#    define PHI_COUNTER() __COUNTER__

#else

#    define PHI_COUNTER() __LINE__

#endif

#endif // INCG_PHI_CORE_COMPILER_SUPPORT_COUNTER_HPP
