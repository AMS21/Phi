#ifndef INCG_PHI_CORE_MATH_IS_INFINITY_HPP
#define INCG_PHI_CORE_MATH_IS_INFINITY_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/intrinsics/is_infinity.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/compiler_support/warning.hpp"
#include "phi/type_traits/enable_if.hpp"
#include "phi/type_traits/is_safe_floating_point.hpp"
#include "phi/type_traits/is_unsafe_floating_point.hpp"

// TODO: Don't require standard limits
#if !PHI_SUPPORTS_IS_INFINITY()
#    include <limits>
#endif

DETAIL_PHI_BEGIN_NAMESPACE()

PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Wfloat-equal")
PHI_CLANG_SUPPRESS_WARNING_PUSH()
PHI_CLANG_SUPPRESS_WARNING("-Wfloat-equal")

template <typename FloatT>
PHI_NODISCARD constexpr enable_if_t<is_unsafe_floating_point<FloatT>::value, bool> is_infinity(
        FloatT value) noexcept
{
#if PHI_SUPPORTS_IS_INFINITY()
    return PHI_IS_INFINITY(value);
#else
    return (value == std::numeric_limits<FloatT>::infinity()) ||
           (-value == std::numeric_limits<FloatT>::infinity());
#endif
}

template <typename FloatT>
PHI_NODISCARD constexpr enable_if_t<is_safe_floating_point<FloatT>::value, bool> is_infinity(
        FloatT value) noexcept
{
    return is_infinity<typename FloatT::value_type>(value.get());
}

PHI_CLANG_SUPPRESS_WARNING_POP()
PHI_GCC_SUPPRESS_WARNING_POP()

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_MATH_IS_INFINITY_HPP
