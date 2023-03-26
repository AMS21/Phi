#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_RVALUE_EXPR_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_RVALUE_EXPR_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"

#if !defined(PHI_IS_RVALUE_EXPR) && !defined(PHI_SUPPORTS_IS_RVALUE_EXPR)

#    if PHI_COMPILER_IS(CLANG_COMPAT)
#        define PHI_IS_RVALUE_EXPR(expr)      __is_rvalue_expr(expr)
#        define PHI_SUPPORTS_IS_RVALUE_EXPR() 1
#    else
#        define PHI_SUPPORTS_IS_RVALUE_EXPR() 0
#    endif

#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_RVALUE_EXPR_HPP
