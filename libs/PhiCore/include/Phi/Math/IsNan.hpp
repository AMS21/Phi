#ifndef INCG_PHI_CORE_MATH_IS_NAN_HPP
#define INCG_PHI_CORE_MATH_IS_NAN_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Nodiscard.hpp"
#include "Phi/TypeTraits/enable_if.hpp"
#include "Phi/TypeTraits/is_safe_floating_point.hpp"
#include "Phi/TypeTraits/is_unsafe_floating_point.hpp"

// Implementation comparison: https://godbolt.org/z/Y7j1oPb5e

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename FloatT>
PHI_NODISCARD constexpr enable_if_t<is_unsafe_floating_point<FloatT>::value, bool> IsNaN(
        FloatT val) noexcept
{
    return val != val;
}

template <typename FloatT>
PHI_NODISCARD constexpr enable_if_t<is_safe_floating_point<FloatT>::value, bool> IsNaN(
        FloatT val) noexcept
{
    return IsNaN<typename FloatT::value_type>(val.get());
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_MATH_IS_NAN_HPP
