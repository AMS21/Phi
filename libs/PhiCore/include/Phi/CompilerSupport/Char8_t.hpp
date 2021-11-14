#ifndef INCG_PHI_CORE_COMPILER_SUPPORT_CHAR8_T_HPP
#define INCG_PHI_CORE_COMPILER_SUPPORT_CHAR8_T_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/CompilerSupport/Features.hpp"
#include "Phi/Config/Warning.hpp"

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
