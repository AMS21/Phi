#ifndef INCG_PHI_CORE_COMPILER_SUPPORT_NORETURN_HPP
#define INCG_PHI_CORE_COMPILER_SUPPORT_NORETURN_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"
#include "phi/compiler_support/features.hpp"

#if PHI_HAS_FEATURE_ATTRIBUTE_NORETURN()

#    define PHI_NORETURN [[noreturn]]

#elif PHI_COMPILER_IS(GCC) || PHI_COMPILER_IS(CLANG_COMPAT)

#    define PHI_NORETURN __attribute__((noreturn))

#elif PHI_COMPILER_IS(MSVC)

#    define PHI_NORETURN __declspec(noreturn)

#else

#    define PHI_NORETURN /* Nothing */

#endif

#endif // INCG_PHI_CORE_COMPILER_SUPPORT_NORETURN_HPP
