#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_RVALUE_EXPR_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_RVALUE_EXPR_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Features.hpp"

#if PHI_HAS_INTRINSIC_IS_RVALUE_EXPR()
#    define PHI_IS_RVALUE_EXPR(expr)      __is_rvalue_expr(expr)
#    define PHI_SUPPORTS_IS_RVALUE_EXPR() 1
#elif PHI_HAS_INTRINSIC_IS_RVALUE_REFERENCE()
#    define PHI_IS_RVALUE_EXPR(expr)      (!__is_reference(decltype((expr))))
#    define PHI_SUPPORTS_IS_RVALUE_EXPR() 1
#else
#    define PHI_IS_RVALUE_EXPR(type)      false
#    define PHI_SUPPORTS_IS_RVALUE_EXPR() 0
#endif

#if defined(PHI_CONFIG_NO_INTRINSICS)
#    undef PHI_SUPPORTS_IS_RVALUE_EXPR
#    define PHI_SUPPORTS_IS_RVALUE_EXPR() 0
#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_RVALUE_EXPR_HPP
