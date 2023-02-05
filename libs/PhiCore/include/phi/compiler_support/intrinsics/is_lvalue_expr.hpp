#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_LVALUE_EXPR_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_LVALUE_EXPR_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/generated/compiler_support/features.hpp"

#if !defined(PHI_IS_LVALUE_EXPR) && !defined(PHI_SUPPORTS_IS_LVALUE_EXPR)
#    if PHI_HAS_INTRINSIC_IS_LVALUE_EXPR()
#        define PHI_IS_LVALUE_EXPR(expr)      __is_lvalue_expr(expr)
#        define PHI_SUPPORTS_IS_LVALUE_EXPR() 1
#    elif PHI_HAS_INTRINSIC_IS_LVALUE_REFERENCE()
#        define PHI_IS_LVALUE_EXPR(expr)      __is_lvalue_reference(decltype((expr)))
#        define PHI_SUPPORTS_IS_LVALUE_EXPR() 1
#    else
#        define PHI_SUPPORTS_IS_LVALUE_EXPR() 0
#    endif
#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_LVALUE_EXPR_HPP
