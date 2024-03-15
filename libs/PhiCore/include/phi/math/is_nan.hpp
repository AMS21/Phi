#ifndef INCG_PHI_CORE_MATH_IS_NAN_HPP
#define INCG_PHI_CORE_MATH_IS_NAN_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/compiler_support/noexcept.hpp"
#include "phi/compiler_support/warning.hpp"
#include "phi/type_traits/enable_if.hpp"
#include "phi/type_traits/is_safe_floating_point.hpp"
#include "phi/type_traits/is_unsafe_floating_point.hpp"

// Implementation comparison: https://godbolt.org/z/Y7j1oPb5e

DETAIL_PHI_BEGIN_NAMESPACE()

PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Wfloat-equal")

template <typename FloatT>
PHI_NODISCARD PHI_CONSTEXPR enable_if_t<is_unsafe_floating_point<FloatT>::value, bool> is_nan(
        FloatT val) PHI_NOEXCEPT
{
    // NOLINTNEXTLINE(misc-redundant-expression)
    return val != val;
}

template <typename FloatT>
PHI_NODISCARD PHI_CONSTEXPR enable_if_t<is_safe_floating_point<FloatT>::value, bool> is_nan(
        FloatT val) PHI_NOEXCEPT
{
    return is_nan<typename FloatT::value_type>(val.unsafe());
}

PHI_GCC_SUPPRESS_WARNING_POP()

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_MATH_IS_NAN_HPP
