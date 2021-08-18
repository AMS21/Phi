#ifndef INCG_PHI_CORE_COMPILER_SUPPORT_CHAR8_T_HPP
#define INCG_PHI_CORE_COMPILER_SUPPORT_CHAR8_T_HPP

#include "Phi/Config/CPlusPlus.hpp"
#include "Phi/Config/Compiler.hpp"
#include "Phi/Config/Warning.hpp"
#include "Phi/PhiConfig.hpp"

PHI_CLANG_SUPPRESS_WARNING_PUSH()
PHI_CLANG_SUPPRESS_WARNING("-Wc++20-compat")

#if PHI_CPP_STANDARD_IS_ATLEAST(20)
#    if PHI_COMPILER_IS_ATLEAST(CLANG, 9, 0, 0)
// Clang supports char8_t since version 9.0
#    elif PHI_COMPILER_IS_ATLEAST(GCC, 7, 0, 0)
// GCC supports char8_t since version 7.0
#    elif PHI_COMPILER_IS_ATLEAST(MSVC, 19, 22, 0)
// MSVC supports char8_t since version 19.22
#    else
using char8_t = unsigned char;
#    endif
#else
using char8_t = unsigned char;
#endif

PHI_CLANG_SUPPRESS_WARNING_POP()

#endif // INCG_PHI_CORE_COMPILER_SUPPORT_CHAR8_T_HPP
