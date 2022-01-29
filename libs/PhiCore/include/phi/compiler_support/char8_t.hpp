#ifndef INCG_PHI_CORE_COMPILER_SUPPORT_CHAR8_T_HPP
#define INCG_PHI_CORE_COMPILER_SUPPORT_CHAR8_T_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/warning.hpp"
#include "phi/generated/compiler_support/features.hpp"

PHI_CLANG_SUPPRESS_WARNING_PUSH()
PHI_CLANG_SUPPRESS_WARNING("-Wunknown-warning-option")
PHI_CLANG_SUPPRESS_WARNING("-Wc++20-compat")
PHI_CLANG_SUPPRESS_WARNING("-Wc++2a-compat")

#if PHI_HAS_FEATURE_CHAR8_T()
// Compiler has native support for char8_t
#else
using char8_t = unsigned char;
#endif

PHI_CLANG_SUPPRESS_WARNING_POP()

#endif // INCG_PHI_CORE_COMPILER_SUPPORT_CHAR8_T_HPP
