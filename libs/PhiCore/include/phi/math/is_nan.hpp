#ifndef INCG_PHI_CORE_MATH_IS_NAN_HPP
#define INCG_PHI_CORE_MATH_IS_NAN_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/nodiscard.hpp"
#include "phi/type_traits/enable_if.hpp"
#include "phi/type_traits/is_safe_floating_point.hpp"
#include "phi/type_traits/is_unsafe_floating_point.hpp"

// Implementation comparison: https://godbolt.org/z/Y7j1oPb5e

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename FloatT>
PHI_NODISCARD constexpr enable_if_t<is_unsafe_floating_point<FloatT>::value, bool> is_nan(
        FloatT val) noexcept
{
    return val != val;
}

template <typename FloatT>
PHI_NODISCARD constexpr enable_if_t<is_safe_floating_point<FloatT>::value, bool> is_nan(
        FloatT val) noexcept
{
    return is_nan<typename FloatT::value_type>(val.get());
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_MATH_IS_NAN_HPP
